#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo 'Require STM32CubeF7 Path'
  exit 1
fi

if [ ! -d "$1/Drivers/CMSIS/Device/ST/STM32F7xx" ]; then
  echo 'Not Found Path'
  exit 1
fi

cp -r "$1/Drivers/CMSIS/Device/ST/STM32F7xx/Include" Include
find Include -type d | xargs chmod 0755
find Include -type f | xargs chmod 0644
find Include -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Include -type f | xargs perl -p -i -e 's/ +$//;'
find Include -type f | xargs perl -p -i -e 's/\t+$//;'

mkdir Source
cp "$1/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/system_stm32f7xx.c" Source
find Source -type d | xargs chmod 0755
find Source -type f | xargs chmod 0644
find Source -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Source -type f | xargs perl -p -i -e 's/ +$//;'
find Source -type f | xargs perl -p -i -e 's/\t+$//;'

mkdir Assembly
mkdir Linker
cp -r "$1/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/arm" Assembly/ARM
cp -r "$1/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/gcc" Assembly/GCC
cp -r "$1/Drivers/CMSIS/Device/ST/STM32F7xx/Source/Templates/iar" Assembly/IAR
mv Assembly/IAR/linker Linker/IAR
find Assembly -type d | xargs chmod 0755
find Assembly -type f | xargs chmod 0644
find Assembly -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Assembly -type f | xargs perl -p -i -e 's/ +$//;'
find Assembly -type f | xargs perl -p -i -e 's/\t+$//;'
find Linker -type d | xargs chmod 0755
find Linker -type f | xargs chmod 0644
find Linker -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Linker -type f | xargs perl -p -i -e 's/ +$//;'
find Linker -type f | xargs perl -p -i -e 's/\t+$//;'
