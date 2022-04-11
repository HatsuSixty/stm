#!/bin/sh

set -x

#### STM ####

cd ./stm/
./test.py
make
if [ -f "./stm" ]; then
    cp -v ./stm ../bin/stm
fi
cd ..

#############
