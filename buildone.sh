#!/usr/bin/env bash

######### Colored output to console ###### 
#ANSI escape codes:

#Black        0;30     Dark Gray     1;30
#Red          0;31     Light Red     1;31
#Green        0;32     Light Green   1;32
#Brown/Orange 0;33     Yellow        1;33
#Blue         0;34     Light Blue    1;34
#Purple       0;35     Light Purple  1;35
#Cyan         0;36     Light Cyan    1;36
#Light Gray   0;37     White         1;37
#And then use them like this in your script:

RED='\033[0;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'
CYAN='\033[0;36m'

if [[ $# -lt 1 ]]; then
	echo -e "${RED}Usage: buildone.sh <file> <outdir:=./bin/>${NC}"
	return -1
fi

if [[ ! -f $1 ]]; then
	echo -e "${RED}source file $1 not exist!${NC}"
	return -1
fi

outdir=${2:-"./bin"}

if [[ ! -d $outdir ]]; then
	echo -e "${RED}$2 is not a directory!${NC}"
	return -1
fi

filename=$1
outname=${filename##*/}
outname=${outname%.*}
echo -e "Output file: ${CYAN}[ ${outdir}/${outname} ]${NC}"
g++ -std=c++11 -g -Wall $1 ./src/common.cc -o "${outdir}/${outname}"

if [[ $? -eq 0 ]]; then
	echo -e "${GREEN}====== Build Success!=========${NC}"
else
	echo -e "${RED}======= Build Fail ========${NC}"
fi