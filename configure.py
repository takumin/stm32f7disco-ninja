#!/usr/bin/env python3
# encoding:utf-8

import os
import sys
import glob
import configparser
import re
import pprint
import subprocess

class EmbConfig:
    ini = object()
    _objs_ = {}
    _dict_ = {}
    _val_fmt_ = 0
    _bld_fmt_ = 0
    _typ_fmt_ = 0

    # コマンド出力結果取得
    def get_cmd(self, key, cmd):
        # 出力結果取得
        try:
            res = subprocess.check_output(cmd)
        except:
            res = ''
        # 辞書アップデート
        self._objs_.update({key: os.path.abspath(res.strip().decode('utf-8'))})

    # iniファイル読み込み
    def parse_ini(self, path):
        # iniファイルチェック
        if not os.path.exists(os.path.abspath(path)):
            print('Not Found Configuration File...')
            sys.exit(1)

        # iniファイル読み込み
        self.ini = configparser.SafeConfigParser()
        self.ini.read(os.path.abspath(path))

    # インクルードファイル一覧生成
    def gen_inc(self, s):
        for key in self.ini.sections():
            if self.ini.has_option(key, s):
                if os.path.isdir(os.path.abspath(self.ini.get(key, s))):
                    self._dict_.update({key + '_incdir': {'dir': os.path.abspath(self.ini.get(key, s))}})
                    if len(key + '_incdir') > self._val_fmt_:
                        self._val_fmt_ = len(key + '_incdir')

    # ソースファイル一覧生成
    def gen_src(self, s):
        # セクション一覧
        for key in sorted(self.ini.sections()):
            # sourceエントリ
            if self.ini.has_option(key, s):
                # パス取得
                rpath = os.path.relpath(self.ini.get(key, s))
                bpath = os.path.basename(rpath)
                dpath = os.path.abspath(os.path.dirname(rpath))
                spath = []
                opath = []
                # ディレクトリが存在しない場合はスキップ
                if not os.path.exists(dpath):
                    continue
                # ビルドルールタイプが存在しない場合はスキップ
                if not self.ini.has_option(key, 'type'):
                    continue
                # 再帰チェック
                if self.ini.has_option(key, 'recursive'):
                    recursive = True
                    pattern = dpath + '/**/' + bpath
                else:
                    recursive = False
                    pattern = dpath + '/' + bpath
                # ファイルマッチ
                for v in glob.iglob(pattern, recursive=recursive):
                    spath.append('$' + key + '_srcdir/' + v.replace(dpath + '/', ''))
                    opath.append('$builddir/' + key + '/' + re.sub(r'\.(c|s)$', '.o', v.replace(dpath + '/', '')))
                    # ビルド文字列フォーマットカウンタ
                    bld = len('$builddir/' + key + '/' + re.sub(r'\.(c|s)$', '.o', v.replace(dpath + '/', '')))
                    if bld > self._bld_fmt_:
                        self._bld_fmt_ = bld
                # ファイル一覧ソート
                spath = sorted(sorted(spath), key=lambda x: x.count('/'), reverse=True)
                opath = sorted(sorted(opath), key=lambda x: x.count('/'), reverse=True)
                # リストアップデート
                self._dict_.update({key + '_srcdir': {'type': self.ini.get(key, 'type'), 'dir': dpath, 'src': spath, 'obj': opath}})
                # 変数文字列フォーマットカウンタ
                if len(key + '_srcdir') > self._val_fmt_:
                    self._val_fmt_ = len(key + '_srcdir')
                # ルール文字列フォーマットカウンタ
                if len(self.ini.get(key, 'type')) > self._typ_fmt_:
                    self._typ_fmt_ = len(self.ini.get(key, 'type'))

    # Ninjaビルドファイル生成
    def gen_ninja(self, path):
        # リンクターゲット
        if self.ini.has_option('general', 'target'):
            target = self.ini.get('general', 'target')
        else:
            target = '$builddir/$project.elf'
        # デフォルトターゲット
        if self.ini.has_option('general', 'default'):
            default = self.ini.get('general', 'default')
        else:
            default = '$builddir/$project.elf'
        # ファイルオープン
        f = open(path, 'w')
        # Ninjaバージョン
        f.write('#\n')
        f.write('# Require Ninja Version\n')
        f.write('#\n')
        f.write('ninja_required_version = 1.3\n')
        # ユーザー定義変数
        f.write('#\n')
        f.write('# User Variable\n')
        f.write('#\n')
        # プロジェクト名書き込み
        if self.ini.has_option('general', 'project'):
            f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format('project', self.ini.get('general', 'project')))
        else:
            f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format('project', 'project'))
        # ビルドディレクトリ書き込み
        if self.ini.has_option('general', 'builddir'):
            f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format('builddir', self.ini.get('general', 'builddir')))
        # ユーザー変数一覧書き込み
        for k, v in sorted(self._dict_.items()):
            f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format(k, v['dir']))
        # デフォルト変数
        f.write('#\n')
        f.write('# Default Variable\n')
        f.write('#\n')
        # インクルードディレクトリ一覧書き込み
        incs = []
        for k, v in sorted(self._dict_.items()):
            if re.match('.*_incdir$', k):
                incs.append(k)
        f.write(str('{0:<' + str(self._val_fmt_) + '} = -isystem ${1}\n').format('_include_flags', str(' -isystem $'.join(incs))))
        # オブジェクトファイル一覧書き込み
        objs = []
        libs = {}
        flags = []
        for k, v in sorted(self._objs_.items()):
            f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format(k, v))
            objs.append(k)
            if re.match(r'.*\.a$', v):
                lib_file = re.sub(r'.*/', '', v)
                lib_name = re.sub(r'^lib([a-zA-Z0-9]+)\.a$', '\\1', lib_file)
                lib_dirs = os.path.dirname(v)
                if lib_name not in libs:
                    libs.update({lib_name: lib_dirs})
        f.write(str('{0:<' + str(self._val_fmt_) + '} = ${1}\n').format('_require_objs', str(' $'.join(objs))))
        f.write(str('{0:<' + str(self._val_fmt_) + '} = ').format('_ldflags'))
        for k, v in sorted(libs.items()):
            flags.append('-L')
            flags.append(v)
            flags.append('-l')
            flags.append(k)
        f.write('{0}\n'.format(' '.join(flags)))
        # コンパイルフラグ書き込み
        f.write('#\n')
        f.write('# Compiler Flags\n')
        f.write('#\n')
        if self.ini.has_section('flags'):
            for k, v in self.ini.items('flags'):
                f.write(str('{0:<' + str(self._val_fmt_) + '} = {1}\n').format(k, v))
        # ルール一覧書き込み
        if self.ini.has_section('rules'):
            for k, v in self.ini.items('rules'):
                f.write('#\n')
                f.write('# Rule {0}\n'.format(k))
                f.write('#\n')
                f.write('rule {0}\n'.format(k))
                if re.match(r'(gcc|clang).*-MF \$out\.d', v):
                    f.write('  depfile = $out.d\n'.format(v))
                f.write('  command = {0}\n'.format(v))
                f.write('  description = {0} $in\n'.format(k))
        # ビルド一覧書き込み
        for k, v in sorted(self._dict_.items()):
            if 'src' in v and 'obj' in v and len(v['src']) == len(v['obj']):
                f.write('#\n')
                f.write('# Build {0}\n'.format(k.replace('_srcdir', '')))
                f.write('#\n')
                for i in range(len(v['src'])):
                    bld_fmt = ' ' * (self._bld_fmt_ - len(v['obj'][i]))
                    typ_fmt = v['type'] + ' ' * (self._typ_fmt_ - len(v['type']))
                    f.write(str('build {0}: {1} {2} {3}\n').format(v['obj'][i], bld_fmt, typ_fmt, v['src'][i]))
        # リンカー
        f.write('#\n')
        f.write('# Link\n')
        f.write('#\n')
        f.write('build {0}: link $\n'.format(target))
        objs = []
        for k, v in sorted(self._dict_.items()):
            if 'obj' in v:
                for o in v['obj']:
                    objs.append(o)
        for i in range(len(objs)):
            if len(objs) - 1 != i:
                f.write('      {0} $\n'.format(objs[i]))
            else:
                f.write('      {0}\n'.format(objs[i]))
        # ターゲット一覧書き込み
        if self.ini.has_section('targets'):
            for k, v in self.ini.items('targets'):
                f.write('#\n')
                f.write('# Target {0}\n'.format(k))
                f.write('#\n')
                f.write('build {0}: {1}\n'.format(k, v))
        # デフォルトターゲット
        f.write('#\n')
        f.write('# Default Target\n')
        f.write('#\n')
        f.write(str('default {0}\n').format(default))
        # ファイルクローズ
        f.close()

    # コンストラクタ
    def __init__(self, path):
        # iniファイル読み込み
        self.parse_ini(path)

        # 辞書生成
        self.gen_inc('include')
        self.gen_src('source')
        sorted(self._dict_)

# Ninjaビルドファイル生成クラス
config = EmbConfig(os.path.join(os.path.dirname(__file__), os.path.realpath('./configure.ini')))

# 標準オブジェクト一覧
config.get_cmd('_libgcc_a', ['arm-none-eabi-gcc', '-mthumb', '-march=armv7e-m', '-mcpu=cortex-m7', '-mfloat-abi=hard', '-mfpu=fpv5-sp-d16', '-print-file-name=libgcc.a'])

# Ninjaビルドファイル生成
config.gen_ninja(os.path.join(os.path.dirname(__file__), os.path.realpath('./build.ninja')))
