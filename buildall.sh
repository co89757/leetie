#!/usr/bin/env bash

## build all problem solutions under src/ except for common.cc and drop the binaries into bin

RED='\033[0;31m'
NC='\033[0m' # No Color
GREEN='\033[0;32m'
CYAN='\033[0;36m'

if [[ $# -lt 1 ]]; then
  echo "Usage: buildall.sh [-r|--run] [-o|--outdir] <cpp_files_to_build> "
  exit -1
fi


SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
RUNALL=0
OUTDIR=${SCRIPT_DIR}/bin 
FILES=""
while [[ $# -ge 1 ]]; do
  key=$1
  case $key in
    -r| --run )
      RUNALL=1
      ;;
    -o|--outdir)
      OUTDIR="$2"
      shift ## pass argument
      ;;
    *)
      FILES=$*
      break
      ;;

  esac
  shift #pass argument/value 
done

if [[ ! -d $OUTDIR ]]; then
  echo -e "${RED}OUTDIR: ${OUTDIR} is not valid directory ${NC}"
  exit -1
fi

echo -e "FILES: ${CYAN}$FILES ${NC}"

## now build sources 
for file in $FILES ; do
  basename=${file##*/}
  basename=${basename%.*}
  echo -e "\n---- building $basename----"
  bash ./buildone.sh $file $OUTDIR 
  if [[ $? -ne 0 ]]; then
    echo "Fail building: $basename, skipping"
    continue
  fi
  if [[ $RUNALL -eq 1 ]]; then
  	echo -e "-------${CYAN}$basename${NC} OUTPUT ---------"
    "$OUTDIR/$basename"
  fi
done

echo "===== DONE ====="
