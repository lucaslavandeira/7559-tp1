#!/bin/bash
mdkir build
cd build/
cmake ..
make
./Test
