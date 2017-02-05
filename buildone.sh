#!/usr/bin/env bash

if [[ $# -ne 2 ]]; then
	echo "Usage: buildone.sh <file> -o <out>"
	return -1
fi

g++ -std=c++11 -g -Wall $1 ./src/common.cc -o $2

if [[ $? -eq 0 ]]; then
	echo "====== Build Success!========="
else
	echo "======= Build Fail ========"
fi