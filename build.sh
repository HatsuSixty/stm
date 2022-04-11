#!/bin/sh

#### STM ####

cd ./stm/
./test.py
make
if [ -f "./stm" ]; then
    cp ./stm ../bin/stm
fi
cd ..

#############
