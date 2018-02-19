#!/bin/bash

cd ./gklsS4d/opt_point && \
../../../build/multievolvent-sample -c gklsS -d 4 -t rotated    -e 0.01 -r 4.5 -q 5 -s -i 250000
../../../build/multievolvent-sample -c gklsS -d 4 -t multilevel -e 0.01 -r 4.5 -q 5 -s -i 250000 -m 9
