#!/bin/sh

set -e

if [ ! -d "$1" ]; then
  echo 'Require CMSIS SVD Directory'
  exit 1
fi

cp -r "$1" Files
find Files -type d | xargs chmod 0755
find Files -type f | xargs chmod 0644
find Files -type f | xargs perl -p -i -e 's/\r\n/\n/g;'
find Files -type f | xargs perl -p -i -e 's/ +$//;'
find Files -type f | xargs perl -p -i -e 's/\t+$//;'
