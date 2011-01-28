#!/bin/bash
g++ -O2 -Wall -I. -I/usr/local/include/c-client-src zookeeper/*.cpp *.cpp -lzookeeper_mt && ./a.out
