#!/bin/bash

cd ./gklsS3d/same_r/opt_point && \
../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 1 -r 4.5 -s -i 250000
../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 2 -r 4.5 -s -i 300000
../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.01 -E 0.05 -l 3 -r 4.5 -s -i 300000
../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 1 -r 4.5 -s -i 300000
../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 2 -r 4.5 -s -i 300000
../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -E 0.05 -l 3 -r 4.5 -s -i 300000
#../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.01 -l 4 -r 3.1 -s -i 100000
