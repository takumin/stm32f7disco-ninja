#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo 'Require STM32CubeF7 Path'
  exit 1
fi

if [ ! -d "$1/Drivers/STM32F7xx_HAL_Driver" ]; then
  echo 'Not Found Path'
  exit 1
fi

cp -r "$1/Drivers/STM32F7xx_HAL_Driver/Inc" Include
find Include -type d | xargs chmod 0755
find Include -type f | xargs chmod 0644
find Include -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Include -type f | xargs perl -p -i -e 's/ +$//;'
find Include -type f | xargs perl -p -i -e 's/\t+$//;'

cp -r "$1/Drivers/STM32F7xx_HAL_Driver/Src" Source
find Source -type d | xargs chmod 0755
find Source -type f | xargs chmod 0644
find Source -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Source -type f | xargs perl -p -i -e 's/ +$//;'
find Source -type f | xargs perl -p -i -e 's/\t+$//;'

mkdir Template
chmod 0755 Template
find Include -type f -name '*_template.h' -exec mv {} Template \;
find Source -type f -name '*_template.c' -exec mv {} Template \;
