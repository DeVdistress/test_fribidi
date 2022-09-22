#!/bin/bash
##
## A; B    # Run A and then B, regardless of success of A
## A && B  # Run B if and only if A succeeded
## A || B  # Run B if and only if A failed
## A &     # Run A in background.
## 
## cmake -B build && cd ./build && make clean && make all && ./test_fribidi ; cd ../

echo مرحبا بالعالم

cmake -B build && make -C $(pwd)/build/ clean; make -C $(pwd)/build/ all && ./build/test_fribidi