#!/bin/bash

cd ./gklsS2d/same_r/accuracy && \
../../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 1 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 2 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t rotated -E 0.05 -a -e 0.005 -l 3 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 1 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 2 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 3 -r 4.6 -s -i 200000
../../../../build/multievolvent-sample -c gklsS -t shifted -E 0.05 -a -e 0.005 -l 4 -r 4.6 -s -i 200000

../../../../build/multievolvent-sample -c gklsS -t noninjective -e 0.005 -i 20000 -a -s -r 4.6
