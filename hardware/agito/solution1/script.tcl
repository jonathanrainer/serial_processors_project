############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project agito
add_files agito/source/agito.cpp
add_files agito/source/agito.h
open_solution "solution1"
set_part {xc6slx45csg324-3}
create_clock -period 20 -name default
#source "./agito/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
