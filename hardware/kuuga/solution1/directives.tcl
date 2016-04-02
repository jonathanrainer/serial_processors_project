############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
set_directive_loop_tripcount -min 1 -max 50 -avg 15 "kuuga/main_loop"
set_directive_resource -core RAM_2P_BRAM "kuuga" memory
set_directive_pipeline "bit_serial_add/add_loop"
