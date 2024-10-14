#!/bin/sh
rm -r build
cmake -Bbuild
cd build
make
./CPSC453A2

