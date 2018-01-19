#!/bin/bash

cd ./gklsS2d/opt_point && \
../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 1 -r 4.6 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 2 -r 3.7 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 3 -r 3.4 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 1 -r 4.8 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 2 -r 4.7 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 3 -r 3.7 -s -i 25000
../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 4 -r 3.5 -s -i 100000

../../../build/multievolvent-sample -c gklsS -t noninjective -e 0.01 -i 10000 -r 3.9 -s
