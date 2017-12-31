#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo 'Require Binary: $1'
  exit 1
fi

CURDIR="`realpath $(dirname $0)`"
GDBPATH="`which arm-none-eabi-gdb`"

xterm +u8 -e openocd -f "${CURDIR}/stm32f7disco.cfg" &

PID=$!

sleep 1

xterm +u8 -e arm-none-eabi-gdb -q --tui --command=${CURDIR}/debug.gdb $1

kill $PID
