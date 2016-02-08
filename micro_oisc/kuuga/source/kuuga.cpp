//  *(ram + 0xA8001000/sizeof(int)) = 47;
//	*(ram + base_addr) = base_addr;
//	*(ram + base_addr + 1) = pc;

#include "kuuga.h"

void subleq(uint32 * pc, volatile int * ram, int base_addr,
		uint10 a, uint10 b, uint10 c);
//void print_memory(volatile int * ram);

int kuuga(volatile int * ram, int base_addr) {
	// AXI4 Master Interface
	#pragma HLS INTERFACE ap_bus port=ram bundle=MAXI
	#pragma HLS RESOURCE core=AXI4M variable=ram

	// AXI4 LITE
	#pragma HLS RESOURCE core=AXI4LiteS variable=return metadata="-bus_bundle AXILiteS"

	#pragma HLS INTERFACE ap_none register     port=base_addr
	#pragma HLS RESOURCE core=AXI4LiteS    variable=base_addr metadata="-bus_bundle AXILiteS"

	uint32 pc = 0;
	uint32 inst = *(ram + base_addr);

	// Execute until the halt bit is set.
	while ((inst & 0x00000001) <= 0)
	{
		uint10 a = ((inst & 0xFFC00000) >> 22);
		uint10 b = ((inst & 0x003FF000) >> 12);
		uint10 c = ((inst & 0x00000FFC) >> 2);
		subleq(&pc, ram, base_addr, a, b, c);
		inst = *(ram + base_addr + pc);
	}
	return 0;
}

void subleq(uint32 * pc, volatile int * ram, int base_addr,
		uint10 a, uint10 b,uint10 c)
{
	int32 m_a = *(ram + base_addr + (int) a);
	int32 m_b = *(ram + base_addr + (int) b);
	int32 check = m_b - m_a;
	if(check <= 0)
	{
		*pc = base_addr+c;
	}
	else
	{
		*pc = *pc+1;
	}
	*(ram + base_addr + (int) b) = check;
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
