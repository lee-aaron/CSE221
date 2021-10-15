#!/bin/bash

if [ ! -d "src/obj" ]; then
  mkdir -p src/obj
fi

if [ ! -d "src/results" ]; then
  mkdir -p -m 777 src/results
fi

if [ ! -f "src/cpu_main" ]; then
  make
fi

sudo nice -n -20 ./src/cpu_main