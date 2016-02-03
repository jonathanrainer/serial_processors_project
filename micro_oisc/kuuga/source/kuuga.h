#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

#ifndef UART_BASE_ADDR
#define UART_BASE_ADDR 0x10180000
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>
#include <hls_stream.h>

//Typedefs
typedef ap_uint<32> uint32;
typedef ap_int<32> int32;



#endif
