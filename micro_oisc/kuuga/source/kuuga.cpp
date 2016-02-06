//*(ram + 0xA8001000/sizeof(int)) = 47;

#include "kuuga.h"

uint32 fetch(int * pc, volatile int * ram);
void subleq(int * pc, volatile int * ram, uint10 a, uint10 b, uint10 c);
//void print_memory(volatile int * ram);

int kuuga(volatile int * ram, int * pc) {
	// AXI4 Master Interface
	#pragma HLS INTERFACE ap_bus port=ram bundle=MAXI
	#pragma HLS RESOURCE core=AXI4M variable=ram

	// AXI4 LITE
	#pragma HLS RESOURCE core=AXI4LiteS variable=return metadata="-bus_bundle AXILiteS"

	#pragma HLS INTERFACE ap_none register     port=pc
	#pragma HLS RESOURCE core=AXI4LiteS    variable=pc metadata="-bus_bundle AXILiteS"

	uint32 inst = fetch(pc, ram);
	// Execute until the halt bit is set.
	while ((inst & 0x00000001) <= 0)
	{
		uint10 a = ((inst & 0xFFC00000) >> 22);
		uint10 b = ((inst & 0x003FF000) >> 12);
		uint10 c = ((inst & 0x00000FFC) >> 2);
		subleq(pc, ram, a, b, c);
		inst = fetch(pc, ram);
	}
	// Execute the instruction directly, no decode is required as there is only
	// one instruction
	return 0;
}

uint32 fetch(int * pc, volatile int * ram)
{
	return *(ram + (*pc));
}

void subleq(int * pc, volatile int * ram, uint10 a, uint10 b,uint10 c)
{
	int32 m_a = ram[(int) a];
	int32 m_b = ram[(int) b];
	int32 check = m_b - m_a;
	if(check <= 0)
	{
		*pc = c;
	}
	else
	{
		*pc = *pc+1;
	}
	ram[(int) b] = check;
	return;
}

//void print_memory(volatile int * ram)
//{
//	printf("Memory: [\n");
//	for (int j=0; j < 50; j++)
//	{
//		if (j % 4 == 0 && j != 0)
//		{
//			printf("\n");
//		}
//		printf("0x%08X,", (int) ram[j]);
//	}
//	printf("]\n");
//}
