#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

	// Includes
	#include <stdio.h>
	#include <stdlib.h>
	#include <ap_int.h>

	//Typedefs
	typedef ap_uint<32> uint32;
	typedef ap_int<32> int32;
	typedef ap_uint<10> uint10;
	typedef ap_uint<5> uint5;
	typedef ap_uint<1> uint1;

	// Prototypes
	int agito(volatile int * ram, int base_addr);
	uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag);
	//void print_memory(volatile int * ram);


#endif
