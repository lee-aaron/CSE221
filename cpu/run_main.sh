#!/bin/bash

sudo taskset -c 0 nice -n -20 ./src/cpu_main