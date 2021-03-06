# CSE221 - Operating Systems Project

## CPU

To run the CPU test, you just need to `cd cpu` and run `./run-main.sh`. It will run all the tests in the folder.

## Memory

To run the Memory test, you just need to `cd memory` and run `./run-main.sh`. It will run all the tests in the folder.

## Network

To run network tests, you need to `cd network` and run `./run-main.sh` with parameters. The python files in the folder are used to analyze the clock cycles reported by the tests and output the corresponding metrics (ie graph or GB/s).

To run the RTT tests, you need to add the `rtt_c <ip> <port>` argument to start the client and `rtt_s <ip> <port>` to start the server. Make sure the server is running before starting the client.

To run BW tests, you need add the `bw_c <ip> <port>` argument to start the client and `bw_s <ip> <port>` to start the server. Make sure the server is running before starting the client.

To run the connection overhead tests, you need to add the `conn_c <ip> <port>` argument to start the client and `conn_s <ip> <port>` to start the server. Make sure the server is running before starting the client.

## File System

To run file system tests, you need to `cd fs` and run `./run-main.sh` with parameters.

To run the cache test, you need to add `cache` argument to the bash script to test it. The code will automatically generate files to measure the cache size.

To run the sequential read test, you need to add `seq` argument to the bash script to test it. The code will automatically generate files to measure the average per block read time.

To run the random access read test, you need to add `rand` argument to the bash script to test it. The code will automatically generate files to measure the average per block read time.

To run the contention test, you need to add `contention` argument to the bash script to test it. The code will automatically generate files to measure the block reading time when there are 1 to 16 processes.