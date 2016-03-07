############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project kuuga
set_top kuuga
add_files kuuga/source/kuuga.h
add_files kuuga/source/kuuga.cpp
add_files -tb kuuga/source/kuuga_testbench.cpp
open_solution "solution1"
set_part {xc7vx485tffg1761-2}
create_clock -period 2.12 -name default
set_clock_uncertainty 0.01ns
source "./kuuga/solution1/directives.tcl"
csim_design -ldflags {-B"/usr/lib/x86_64-linux-gnu/"}
csynth_design
cosim_design -ldflags {-B"/usr/lib/x86_64-linux-gnu/"}
export_design -format ip_catalog
