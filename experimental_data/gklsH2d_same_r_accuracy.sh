#!/bin/bash

cd ./gklsH2d/same_r/accuracy && \
#../../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.001 -a -q 4 -l 1 -r 7.0 -s -i 300000
#../../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.001 -a -q 4 -l 2 -r 7.0 -s -i 300000
#../../../../build/multievolvent-sample -c gklsH -t rotated -E 0.05 -e 0.001 -a -q 4 -l 3 -r 7.0 -s -i 300000
../../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.001 -a -q 4 -l 1 -r 7.0 -s -i 300000
../../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.001 -a -q 4 -l 2 -r 7.0 -s -i 300000
../../../../build/multievolvent-sample -c gklsH -t shifted -E 0.05 -e 0.001 -a -q 4 -l 3 -r 7.0 -s -i 300000
#../../../build/multievolvent-sample -c gklsH -t shifted -e 0.01 -l 4 -r 3.5 -s -i 120000

../../../../build/multievolvent-sample -c gklsH -t noninjective -e 0.001 -i 70000 -r 7.0 -a -s
