#!/bin/bash

cd ./f_gr/same_r/accuracy && \
../../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -E 0.05 -a -l 1 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -E 0.05 -a -l 2 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t rotated -e 0.001 -E 0.05 -a -l 3 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -E 0.05 -a -l 1 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -E 0.05 -a -l 2 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t shifted -e 0.001 -E 0.05 -a -l 3 -r 3.1 -s -i 50000
../../../../build/multievolvent-sample -c grish -t shifted -e 0.003 -E 0.05 -a -l 4 -r 3.1 -s -i 50000

../../../../build/multievolvent-sample -t noninjective -e 0.001 -i 10000 -c grish -a -s -r 3.1
