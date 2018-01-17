#!/bin/bash

cd ./gklsS2d/same_r/opt_point && \
../../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 1 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 2 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t rotated -e 0.01 -l 3 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 1 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 2 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 3 -r 5.0 -E 0.05 -s -i 170000
../../../../build/multievolvent-sample -c gklsS -t shifted -e 0.01 -l 4 -r 5.0 -E 0.05 -s -i 170000

../../../../build/multievolvent-sample -c gklsS -t noninjective -e 0.01 -i 10000 -r 5.0 -s
