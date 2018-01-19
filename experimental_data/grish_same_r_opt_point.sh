#!/bin/bash

cd ./f_gr/same_r/opt_point && \
../../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 1 -r 3.0 -s -i 50000
../../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 2 -r 3.0 -s -i 50000
../../../../build/multievolvent-sample -c grish -t rotated -e 0.01 -l 3 -r 3.0 -s -i 50000
../../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 1 -r 3.0 -s -i 50000 -E 0.05
../../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 2 -r 3.0 -s -i 50000 -E 0.05
../../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 3 -r 3.0 -s -i 50000 -E 0.05
../../../../build/multievolvent-sample -c grish -t shifted -e 0.01 -l 4 -r 3.0 -s -i 50000 -E 0.05

../../../../build/multievolvent-sample -t noninjective -e 0.01 -i 10000 -c grish -r 3.0 -s
