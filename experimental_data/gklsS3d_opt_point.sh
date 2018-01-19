#!/bin/bash

cd ./gklsS3d/opt_point && \
../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 1 -r 4.5 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 2 -r 3.4 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 3 -r 3.3 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 1 -r 4.3 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 2 -r 3.6 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 3 -r 3.2 -s -i 250000
#../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -l 4 -r 3.1 -s -i 100000

../../../build/multievolvent-sample -c gklsS -d 3 -t noninjective -e 0.01 -i 50000 -s -r 3.7
