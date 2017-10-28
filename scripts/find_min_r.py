#!/usr/bin/env python
# -*- coding: utf-8 -*-

import re
import sys
import os
import subprocess
import numpy as np

def run_sample(execPath, args, r):
    assert os.path.exists(execPath)

    command = execPath + ' ' + args + ' -r ' + str(r)
    print(command)

    PIPE = subprocess.PIPE
    p = subprocess.Popen(command, shell = True, stdin = PIPE, stdout = PIPE,
        stderr = subprocess.STDOUT)
    p.wait()
    return p.stdout.read().decode("utf-8")

def main():
    assert len(sys.argv) == 5
    #input: exec_path arguments, range a_b step
    exec_path = sys.argv[1]
    arguments = sys.argv[2]
    low_r = float(sys.argv[3].split('_')[0])
    high_r = float(sys.argv[3].split('_')[1])
    step = float(sys.argv[4])
    n_samples = int((high_r - low_r) / step) + 1
    grid = np.linspace(low_r, high_r, num = n_samples, endpoint = True)

    print(grid)

    min_r = None
    min_found = False

    for r in grid:
        output = run_sample(exec_path, arguments, r)
        problems_solved = int(re.findall('Problems solved: (\d+)', output)[0])
        if problems_solved is 100 and min_found is False:
            min_found = True
            min_r = r

    print('Optimal r is {}'.format(min_r))

if __name__ == '__main__':
    main()
