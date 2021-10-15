#!/usr/bin/python3
import sys

import matplotlib.pyplot as plt
import numpy as np


def show_histogram(datas):
    plt.hist(datas, bins='auto')
    plt.show()


if __name__ == '__main__':
    fin = open(sys.argv[1]) if len(sys.argv) > 1 else sys.stdin
    dataso = [int(x) for x in fin.read().split()]
    avg = np.average(dataso)
    std = np.std(dataso)
    twosigma = avg + std * 2
    datas = [x for x in dataso if x <= twosigma]

    print(f'Average: {np.average(datas)}')
    print(f'Std dev: {np.std(datas)}')
    print(f'Length:  {len(datas)}')

    # show_histogram(dataso)
    # show_histogram(datas)
