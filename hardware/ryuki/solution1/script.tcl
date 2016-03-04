############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project ryuki
set_top ryuki
add_files ryuki/source/ryuki.cpp
add_files ryuki/source/ryuki.h
add_files -tb ryuki/source/testbench.cpp
open_solution "solution1"
set_part {xc7vx485tffg1761-2}
create_clock -period 10 -name default
source "./ryuki/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
