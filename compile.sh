#!/bin/bash
g++ -O2 -Wall -I. -I/usr/local/include/c-client-src zookeeper/*.cpp hbase/*.cpp *.cpp -lzookeeper_mt && ./a.out
