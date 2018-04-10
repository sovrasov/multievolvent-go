#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
import numpy as np

matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['mathtext.rm'] = 'serif'

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('points_files', metavar='points', type=str, nargs='+',
                        help='paths to the files with points to plot')
    parser.add_argument('--figname', type=str, default='evolvent_plot', help='Name of the output file.')
    parser.add_argument('--show', action='store_true')

    args = parser.parse_args()

    colors = ('b', 'g', 'r', 'c', 'm', 'y', 'k', 'w')
    linestyles = ['-', '--', '-.', ':', ' ', '', ':', '_']

    fig = plt.figure()
    axes = fig.add_axes([0.1, 0.1, 0.8, 0.8])

    for i, points_file in enumerate(args.points_files):
        x, y = [], []
        with open(points_file, 'r') as f:
            for line in f.readlines()[1:]:
                points = line.strip().split(',')
                x.append(float(points[0]))
                y.append(float(points[1]))

        x, y = np.array(x), np.array(y)

        axes.plot(x, y, colors[i] + linestyles[i], alpha = .8)

        axes.set_xlabel('$x$', fontsize=14)
        axes.set_ylabel('$y$', fontsize=14)
        axes.grid(linestyle='dashed', linewidth=0.5)

    if args.show:
        plt.show()
    else:
        plt.savefig(args.figname + '.pdf')
if __name__ == '__main__':
    main()
