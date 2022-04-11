#!/bin/sh

set -x

#### STM ####

cd ./stm/
make
./test.py
if [ -f "./stm" ]; then
    cp -v ./stm ../bin/stm
fi
cd ..

#############
