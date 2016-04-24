#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

	// Includes

	#include <stdio.h>
	#include <stdlib.h>
	#include <ap_int.h>

	// Typedefs

	typedef ap_uint<32> uint32;
	typedef ap_int<32> int32;
	typedef ap_uint<10> uint10;
	typedef ap_uint<1> uint1;

	// Function Prototypes

	uint32 kuuga(int output_loc);
	uint32 subleq(uint32 pc, uint10 a, uint10 b, uint10 c);
	uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag,
									bool * zero_flag);

	// Constants

	// Size of main memory
	#define MEM_SIZE 1000

	// Globals

	// Global variable to allow simulations to set main memory contents.
	extern uint32 memory[MEM_SIZE];

#endif
