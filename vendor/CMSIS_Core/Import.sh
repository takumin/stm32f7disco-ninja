#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo 'Require CMSIS Core Path'
  exit 1
fi

if [ ! -d "$1/CMSIS/Core/Include" ]; then
  echo 'Not Found Path'
  exit 1
fi

cp -r "$1/CMSIS/Core/Include" Include
find Include -type d | xargs chmod 0755
find Include -type f | xargs chmod 0644
find Include -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Include -type f | xargs perl -p -i -e 's/ +$//;'
find Include -type f | xargs perl -p -i -e 's/\t+$//;'
