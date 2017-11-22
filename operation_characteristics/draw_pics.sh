#!/bin/bash

../scripts/draw_characteristics.py ./f_gr/accuracy/ 4000 grish_accur_op.png
../scripts/draw_characteristics.py ./f_gr/opt_point/ 550 grish_opt_point_op.png

../scripts/draw_characteristics.py ./f_gr/same_r/opt_point/ 700 grish_same_r_opt_point.png
../scripts/draw_characteristics.py ./f_gr/same_r/accuracy/ 6000 grish_same_r_acc.png

../scripts/draw_characteristics.py ./gklsS2d/opt_point/ 1500 gklsS2d_opt_pt_op.png
../scripts/draw_characteristics.py ./gklsS2d/accuracy/ 3500 gklsS2d_acc_op.png

../scripts/draw_characteristics.py ./gklsS2d/same_r/accuracy/ 3400 gkls2d_same_r_opt_pt_op.png
../scripts/draw_characteristics.py ./gklsS2d/same_r/opt_point/ 2000 gklsS2d_same_r_acc_op.png

../scripts/draw_characteristics.py ./gklsH2d/opt_point/ 5000 gklsH2d_opt_pt_op.png
../scripts/draw_characteristics.py ./gklsH2d/same_r/opt_point/ 5500 gklsH2d_same_r_opt_pt_op.png

../scripts/draw_characteristics.py ./gklsS3d/opt_point/ 17000 gklsS3d_opt_pt_op.png
../scripts/draw_characteristics.py ./gklsS3d/same_r/opt_point/ 27000 gklsS3d_same_r_opt_pt_op.png
