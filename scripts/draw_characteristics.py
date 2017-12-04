#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D
from os import listdir
from os.path import isfile, join

matplotlib.style.use('classic')

def readPoints(fileName):
    lines = [line.rstrip('\n') for line in open(fileName)]

    label = lines.pop(0)

    pointsK = []
    pointsP = []

    for line in lines:
        if '=' in line:
            continue
        terms = line.split(',')

        pointsK.append(int(terms[0]))
        pointsP.append(int(terms[1]))

    return np.array(pointsK), np.array(pointsP), label

colors = ('b', 'g', 'r', 'c', 'm', 'y', 'k')
linestyles = ['_', '-', '--', ':', '-.', '', ' ']
markers = []
for m in Line2D.markers:
    try:
        if len(m) == 1 and m != ' ':
            markers.append(m)
    except TypeError:
        pass

def main():
    folder = sys.argv[1]
    iters_limit = int(sys.argv[2])

    logFiles = [folder + f for f in listdir(folder) if isfile(join(folder, f)) and 'csv' in f]
    logFiles = sorted(logFiles)

    plt.xlabel(r'$K$', fontsize=15)
    plt.ylabel(r'$P$', fontsize=15)
    plt.xticks(fontsize=13)
    plt.yticks(fontsize=13)
    if not (iters_limit is 0):
        name = sys.argv[3]
        plt.xlim([0., iters_limit])

    for i, log in enumerate(logFiles):
        K, P, label = readPoints(log)
        plt.plot(K, P / 100., colors[i] + ' ' + markers[i] + ' ', label = label, markersize=5)

    plt.grid()
    plt.legend(loc = 'best', fontsize = 8)
    if not (iters_limit is 0):
        plt.savefig(folder + '/' + name, format = 'pdf', dpi = 300)
    else:
        plt.show()

if __name__ == '__main__':
    main()
