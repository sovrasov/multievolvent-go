#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.lines import Line2D

matplotlib.style.use('classic')

def readPoints(fileName):
    lines = [line.rstrip('\n') for line in open(fileName)]

    label = lines.pop(0)

    pointsK = []
    pointsP = []

    for line in lines:
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
    print(markers)
    plt.xlabel(r'$K$', fontsize=20)
    plt.ylabel(r'$P$', fontsize=20)

    for i in range(1, len(sys.argv)):
        K, P, label = readPoints(sys.argv[i])
        plt.plot(K, P / 100., colors[i] + markers[i] + linestyles[i], label = label)

    plt.legend(loc = 'best', fontsize = 10)
    plt.grid()
    plt.show()

if __name__ == '__main__':
    main()
