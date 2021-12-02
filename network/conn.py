import numpy as np
import os.path

if not os.path.exists("src/results/conn_local.txt"):
  print("Connection Overhead file not found!")
  exit()

data = np.loadtxt("src/results/conn_local.txt")
setup = data[:, 0]
teardown = data[:, 1]
avg_setup = np.mean(setup)
avg_teardown = np.mean(teardown)
std_setup = np.std(setup)
std_teardown = np.std(teardown)
print("Average setup: %.2f" % avg_setup)
print ("Std setup: %.2f" % std_setup)

print("Average teardown: %.2f" % avg_teardown)
print ("Std teardown: %.2f" % std_teardown)