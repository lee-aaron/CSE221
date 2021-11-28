#!/usr/bin/python3
import sys

import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    datafile = sys.argv[1] if len(sys.argv) > 1 else "src/results/cache.txt"
    data = []
    for s in open(datafile):
        size, time = s.split()
        time = float(time) # in clock cycles
        time = time / 2.59 # convert to nano seconds
        data.append([int(size), time])
    data = np.array(data, dtype=object)
    plt.plot(data[:, 0], data[:, 1])
    plt.xlabel("Cache size (GB)")
    plt.ylabel("Block Access Time (ns)")
    plt.show()
