import numpy as np
import os.path

if not os.path.exists("src/results/bw_local.txt"):
  print("Bandwidth file not found!")
  exit()

NS_PER_CYCLE = 2.95
SIZE = 32 * 1e6 # 32 MB msg size
data = SIZE / (np.loadtxt("src/results/bw_local.txt") * NS_PER_CYCLE)
avg = np.average(data)
std = np.std(data)
twosigma = avg + std * 2
datas = [x for x in data if x <= twosigma]
avg = np.average(datas)
std = np.std(datas)
print("Average bandwidth: %.2f GB/s" % (avg))
print("Standard deviation: %.2f GB/s" % (std))