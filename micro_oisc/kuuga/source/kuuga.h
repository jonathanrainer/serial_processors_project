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

	// Prototypes
	int kuuga(volatile int * ram, int * pc);


#endif
