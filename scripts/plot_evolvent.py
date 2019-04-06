#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

matplotlib.rcParams['mathtext.fontset'] = 'cm'
matplotlib.rcParams['mathtext.rm'] = 'serif'

def plot_2d_evolvent(points, style):
    assert points.shape[1] == 2

    x, y = points[:,0], points[:,1]

    fig = plt.figure()
    axes = fig.add_axes([0.1, 0.1, 0.8, 0.8])
    axes.plot(x, y, style, alpha = .8)
    axes.set_xlabel('$y_1$', fontsize=14)
    axes.set_ylabel('$y_2$', fontsize=14)
    axes.set_xticks([-0.5, 0., 0.5])
    axes.set_yticks([-0.5, 0., 0.5])
    axes.grid(linestyle='dashed', linewidth=0.5)

def plot_3d_evolvent(points, style):
    assert points.shape[1] == 3
    x, y, z = points[:,0], points[:,1], points[:,2]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(x, y, z)
    ax.set_xlabel('$y_1$', fontsize=14)
    ax.set_ylabel('$y_2$', fontsize=14)
    ax.set_zlabel('$y_3$', fontsize=14)
    ax.set_xticks([-0.5, 0., 0.5])
    ax.set_yticks([-0.5, 0., 0.5])
    ax.set_zticks([-0.5, 0., 0.5])
    ax.grid(linestyle='dashed', linewidth=0.5)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('points_files', metavar='points', type=str, nargs='+',
                        help='paths to the files with points to plot')
    parser.add_argument('--figname', type=str, default='evolvent_plot', help='Name of the output file.')
    parser.add_argument('--show', action='store_true')

    args = parser.parse_args()

    colors = ('b', 'g', 'r', 'c', 'm', 'y', 'k', 'w')
    linestyles = ['-', '--', '-.', ':', ' ', '', ':', '_']

    for i, points_file in enumerate(args.points_files):
        points = []
        with open(points_file, 'r') as f:
            for line in f.readlines()[1:]:
                coordinates = line.strip().split(',')
                point = []
                for coord in coordinates:
                    point.append(float(coord))
                points.append(point)

        points = np.array(points)
        if points.shape[0] == 2:
            plot_2d_evolvent(points, colors[i] + linestyles[i])
        else:
            plot_3d_evolvent(points, colors[i] + linestyles[i])

    if args.show:
        plt.show()
    else:
        plt.savefig(args.figname + '.pdf')
if __name__ == '__main__':
    main()
