//  *(ram + 0xA8001000/sizeof(int)) = 47;
//	*(ram + base_addr) = base_addr;
//	*(ram + base_addr + 1) = pc;

#include "kuuga.h"

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
	while (bit_serial_and(inst, 1) <= 0)
	{
		uint10 a = (bit_serial_and(inst, 0xFFC00000) >> 22);
		uint10 b = (bit_serial_and(inst, 0x003FF000) >> 12);
		uint10 c = (bit_serial_and(inst, 0x00000FFC) >> 2);
		subleq(&pc, ram, base_addr, a, b, c);
		inst = *(ram + base_addr + pc);
	}
	return 0;
}

void subleq(uint32 * pc, volatile int * ram, int base_addr,
		uint10 a, uint10 b,uint10 c)
{
	int32 m_a = *(ram + bit_serial_add(base_addr, a, false));
	int32 m_b = *(ram + bit_serial_add(base_addr, b, false));
	int32 check = bit_serial_add(m_b, m_a, true);
	if(check <= 0)
	{
		*pc = bit_serial_add(base_addr,c,false);
	}
	else
	{
		*pc = bit_serial_add(*pc,1,false);
	}
	*(ram + bit_serial_add(base_addr, b, false)) = check;
	return;
}

uint32 bit_serial_and(uint32 arg1, uint32 arg2)
{
	uint32 result = 0x00000000;
	for (int i = 0; i < 31; i++)
	{
		uint1 bit_1 = arg1.bit(i);
		uint1 bit_2 = arg2.bit(i);
		result.bit(i) = (bit_1 & bit_2);
	}
	return result;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag)
{
	uint32 new_arg2 = arg2;
	if(sub_flag)
	{
		new_arg2 = ~arg2 + 0x00000001;
	}
	uint32 result = 0x00000000;
	uint1 carry = 0x0;
	for (int i = 0; i < 31; i++)
	{
		uint1 bit_1 = arg1.bit(i);
		uint1 bit_2 = new_arg2.bit(i);
		result.bit(i) = (bit_1 ^ bit_2 ^ carry);
		carry = (bit_1 & bit_2) | (carry & (bit_1 ^ bit_2));
	}
	return result;
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
