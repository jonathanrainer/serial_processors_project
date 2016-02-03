//*(ram + 0xA8001000/sizeof(int)) = 47;

#include "kuuga.h"

uint32 fetch(int * pc, volatile int * ram);
uint32 decode(uint32 instruction);

int kuuga(volatile int * ram, int * pc) {
	// AXI4 Master Interface
	#pragma HLS INTERFACE ap_bus port=ram bundle=MAXI
	#pragma HLS RESOURCE core=AXI4M variable=ram

	// AXI4 LITE
	#pragma HLS RESOURCE core=AXI4LiteS variable=return metadata="-bus_bundle AXILiteS"

	#pragma HLS INTERFACE ap_none register     port=pc
	#pragma HLS RESOURCE core=AXI4LiteS    variable=pc metadata="-bus_bundle AXILiteS"

	// Fetch in the instruction from memory
	uint32 inst = fetch(pc, ram);
	//while (inst != )
	// Execute the instruction directly, no decode is required as there is only
	// one instruction
	return 0;
}

uint32 fetch(int * pc, volatile int * ram) {
	return *(ram + *pc/sizeof(int));
}

uint32 decode(uint32 instruction) {
	return 0;
}

