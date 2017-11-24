#!/bin/bash

cd ./gklsS3d/same_r/accuracy && \
#../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.002 -q 5 -a -E 0.05 -l 1 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.002 -q 5 -a -E 0.05 -l 2 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.002 -q 5 -a -E 0.05 -l 3 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t rotated -e 0.002 -q 5 -a -E 0.05 -l 4 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.002 -q 5 -a -E 0.05 -l 1 -r 4.7 -s -i 500000
../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.002 -q 5 -a -E 0.05 -l 2 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.002 -q 5 -a -E 0.05 -l 3 -r 4.7 -s -i 500000
#../../../../build/multievolvent-sample -c gklsS -d 3 -t shifted -e 0.002 -q 5 -a -E 0.05 -l 4 -r 4.7 -s -i 500000
