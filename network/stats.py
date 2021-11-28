#!/usr/bin/python3
import sys

import numpy as np
if __name__ == "__main__":
    datafile = sys.argv[1] if len(
        sys.argv) > 1 else "src/results/rtt_local.txt"
    data = np.loadtxt(datafile)
    avg = np.average(data)
    std = np.std(data)
    twosigma = avg + std * 2
    datas = [x for x in data if x <= twosigma]

    print('Before')
    print(f'Average: {avg:g}')
    print(f'Std dev: {std:g}')
    print(f'Length:  {len(data)}')
    print()

    print('After')
    print(f'Average: {np.average(datas):g}')
    print(f'Std dev: {np.std(datas):g}')
    print(f'Length:  {len(datas)}')
