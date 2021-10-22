#!/bin/bash
set -e

cd "$(realpath "$(dirname "$0")")"

if [ ! -d "src/obj" ]; then
  mkdir -p src/obj
fi

if [ ! -d "src/results" ]; then
  mkdir -p src/results
fi

make

sudo nice -n -20 ./src/mem_main
