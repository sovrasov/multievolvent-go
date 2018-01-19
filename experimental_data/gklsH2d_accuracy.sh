#!/bin/bash

cd ./gklsH2d/accuracy && \
../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -a -e 0.001 -l 1 -r 7.0 -s -i 100000
../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -a -e 0.001 -l 2 -r 5.7 -s -i 100000
#../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -a -e 0.001 -l 3 -r 3.6 -s -i 100000
../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -a -e 0.001 -l 1 -r 7.0 -s -i 100000
#../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -a -e 0.001 -l 2 -r 4.9 -s -i 100000
#../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -a -e 0.001 -l 3 -r 4.1 -s -i 100000
#../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -a -e 0.001 -l 4 -r 3.5 -s -i 120000

../../../build/multievolvent-sample -c gklsH -t noninjective -e 0.001 -i 30000 -r 6.1 -a -s
