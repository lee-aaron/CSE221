#!/bin/bash
set -e

cd "$(realpath "$(dirname "$0")")"

if [ ! -d "src/obj" ]; then
  mkdir -p src/obj
fi

if [ ! -d "src/results" ]; then
  mkdir -p src/results
fi

if [ ! -d "src/files" ]; then
  mkdir -p src/files
fi

for i in $(seq 0 16); do
    [ -f "src/files/cont$i" ] || dd status=none if=/dev/urandom of="src/files/cont$i" bs=1048576 count=64
done

make

sudo nice -n -20 ./src/fs_main "$@"
