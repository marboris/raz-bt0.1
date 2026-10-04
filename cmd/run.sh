#!/bin/bash

mkdir -p build

c++ -std=c++20 -O3 -pipe -Wall source/main.cpp -pthread -o build/main

#./build/main
