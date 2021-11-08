#!/usr/bin/python3
import sys

import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    datafile = sys.argv[1] if len(sys.argv) > 1 else "src/results/access_time.txt"
    data = []
    for s in open(datafile):
        stride, size, time = s.split()
        data.append([int(stride), int(size), float(time)])
    data = np.array(data, dtype=object)
    strides = np.unique(data[:, 0])
    for s in strides:
        sdata = data[data[:, 0] == s, 1:3].T
        sdata[0] = np.log2(sdata[0].astype(float)).astype(int)
        plt.plot(sdata[0], sdata[1])
    plt.xlabel('log2(array size)')
    plt.ylabel('latency in nanoseconds')
    plt.xticks(sdata[0].astype(int))
    plt.legend(strides, title="Stride (Bytes)")
    plt.show()
