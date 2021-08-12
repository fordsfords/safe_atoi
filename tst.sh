#!/bin/sh
# tst.sh - script to build and run the safe_atoi test program.

gcc -Wall -o safe_atoi safe_atoi.c
if [ $? -ne 0 ]; then exit 1; fi

./safe_atoi $*
