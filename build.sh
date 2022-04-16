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

#### STASM ####

cd ./stasm/
make
if [ -f "./stasm" ]; then
	cp -v ./stasm ../bin/stasm
fi
./test.py
cd ..

###############
