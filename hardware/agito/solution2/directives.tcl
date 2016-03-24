############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2015 Xilinx Inc. All rights reserved.
############################################################
set_directive_resource -core RAM_1P_BRAM "agito" memory
set_directive_loop_tripcount -min 1 -max 15 -avg 8 "agito/main_loop"
set_directive_pipeline "bit_serial_and/and_loop"
set_directive_resource -core RAM_1P_BRAM "agito" registers
set_directive_loop_tripcount -min 0 -max 32 -avg 5 "shift/shift_loop"
set_directive_inline "conditional_branch"
set_directive_unroll "bit_serial_add/add_loop"
