#include "kuuga.h"

volatile int *ram;

int kuuga(int *arg1, int *arg2) {
	// AXI4 Master Interface
	#pragma HLS INTERFACE ap_bus port=ram bundle=MAXI
	#pragma HLS RESOURCE core=AXI4M variable=ram

	// AXI4 LITE
	#pragma HLS RESOURCE core=AXI4LiteS variable=return metadata="-bus_bundle AXILiteS"

	#pragma HLS INTERFACE ap_none register     port=arg1
	#pragma HLS RESOURCE core=AXI4LiteS    variable=arg1 metadata="-bus_bundle AXILiteS"

	#pragma HLS INTERFACE ap_none register     port=arg2
	#pragma HLS RESOURCE core=AXI4LiteS    variable=arg2 metadata="-bus_bundle AXILiteS"

	*(ram + 0xA8001000/sizeof(int)) = 47;
	return 0;
}


