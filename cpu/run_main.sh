#!/bin/bash

if [ ! -d "src/obj" ]; then
  mkdir -p src/obj
fi

if [ ! -f "src/cpu_main" ]; then
  make
fi

sudo taskset -c 0 nice -n -20 ./src/cpu_main