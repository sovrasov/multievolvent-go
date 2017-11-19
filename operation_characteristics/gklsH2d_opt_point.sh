#!/bin/bash

cd ./gklsH2d/opt_point && \
#../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.01 -l 1 -r 6.6 -s -i 120000
#../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.01 -l 2 -r 5.5 -s -i 120000
#../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.01 -l 3 -r 4.6 -s -i 120000
../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.01 -l 1 -r 6.4 -s -i 120000
../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.01 -l 2 -r 6.1 -s -i 120000
../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.01 -l 3 -r 5.7 -s -i 120000
#../../../build/multievolvent-sample -c gklsH -t shifted -e 0.01 -l 4 -r 3.5 -s -i 120000
