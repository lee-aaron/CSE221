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

make

sudo nice -n -20 ./src/fs_main "$@"
