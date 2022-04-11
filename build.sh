#!/bin/sh

set -x

#### STM ####

cd ./stm/
make
if [ -f "./stm" ]; then
    cp -v ./stm ../bin/stm
fi
./test.py
cd ..

#############
