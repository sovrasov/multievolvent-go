#!/bin/bash

cd ./f_gr/accuracy && ../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -a -l 1 -r 3.0 -s -i 15000
../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -a -l 2 -r 2.3 -s -i 15000
../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -a -l 3 -r 2.1 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -a -l 1 -r 3.1 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -a -l 2 -r 2.5 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -a -l 3 -r 2.2 -s -i 15000
../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -a -l 4 -r 2.0 -s -i 15000
