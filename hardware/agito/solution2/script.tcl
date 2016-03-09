############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
open_project agito
set_top agito
add_files agito/source/agito.h
add_files agito/source/agito.cpp
add_files -tb agito/source/agito_testbench.cpp
open_solution "solution2"
set_part {xc7vx485tffg1761-2}
create_clock -period 10 -name default
source "./agito/solution2/directives.tcl"
csim_design -ldflags {-B"/usr/lib/x86_64-linux-gnu/"}
csynth_design
cosim_design -ldflags {-B"/usr/lib/x86_64-linux-gnu/"}
export_design -format ip_catalog
