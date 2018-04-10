#!/bin/bash

cd ./f_gr/opt_point && \
../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 1 -r 3.0 -s -i 15000
../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 2 -r 2.2 -s -i 15000
../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 3 -r 2.1 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 1 -r 2.9 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 2 -r 2.4 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 3 -r 2.0 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 4 -r 2.0 -s -i 15000

../../../build/multievolvent-sample -t noninjective -e 0.01 -i 10000 -c grish -r 2.7 -s

../../../build/multievolvent-sample -t smooth -m 10 -e 0.01 -i 10000 -c grish -r 3 -s
