#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo 'Require FreeRTOS Path'
  exit 1
fi

if [ ! -d "$1/FreeRTOS/Source" ]; then
  echo 'Not Found Path'
  exit 1
fi

mkdir -p Include
find "$1/FreeRTOS/Source/include" -type f -name "*.h" -exec cp {} Include \;
find Include -type d | xargs chmod 0755
find Include -type f | xargs chmod 0644
find Include -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Include -type f | xargs perl -p -i -e 's/ +$//;'
find Include -type f | xargs perl -p -i -e 's/\t+$//;'

mkdir -p Source
find "$1/FreeRTOS/Source" -maxdepth 1 -type f -name "*.c" -exec cp {} Source \;
find Source -type d | xargs chmod 0755
find Source -type f | xargs chmod 0644
find Source -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Source -type f | xargs perl -p -i -e 's/ +$//;'
find Source -type f | xargs perl -p -i -e 's/\t+$//;'

mkdir -p Portable/GCC
mkdir -p Portable/IAR
mkdir -p Portable/RVDS
cp -r "$1/FreeRTOS/Source/portable/GCC/ARM_CM7" Portable/GCC
cp -r "$1/FreeRTOS/Source/portable/IAR/ARM_CM7" Portable/IAR
cp -r "$1/FreeRTOS/Source/portable/RVDS/ARM_CM7" Portable/RVDS
cp -r "$1/FreeRTOS/Source/portable/MemMang" Portable
find Portable -type f -name "*.txt" | xargs rm
find Portable -type f -name "*.url" | xargs rm
find Portable -type d | xargs chmod 0755
find Portable -type f | xargs chmod 0644
find Portable -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Portable -type f | xargs perl -p -i -e 's/ +$//;'
find Portable -type f | xargs perl -p -i -e 's/\t+$//;'
