#!/bin/bash

# clang -lncurses code/main.c

make clean
make
strip sweepMyCMine
make run
