#!/bin/bash

cd ./gklsS2d/accuracy && \
../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 1 -r 4.6 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 2 -r 3.7 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 3 -r 3.6 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 1 -r 5.0 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 2 -r 4.9 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 3 -r 4.1 -s -i 100000
../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 4 -r 3.5 -s -i 120000

../../../build/multievolvent-sample -c gklsS -t noninjective -e 0.005 -i 20000 -a  -s -r 4.0
