#include "kuuga.h"

int mutation_test();
int subleq_test();
int add_test();
int serial_and_test();
int serial_add_test();

int main()
{
	for(int i =0; i<MEM_SIZE; i++)
	{
	  memory[i] = 0;
	}
	return subleq_test();
}

//int mutation_test()
//{
//	memory[1] = {0x0ABBCFF1};
//	kuuga(mem, base_addr);
//	if(mem[0] == 0x0ABBCFF1)
//	{
//		return 0;
//	}
//	return 1;
//}

int subleq_test()
{
	uint32 mem_temp[8] = {
	     0x00803004, 0x00000001, 0x00000004, 0x00000005,
	     0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	for(int i=0; i<4; i++)
	  {
	    memory[i] = mem_temp[i];
	  }
	kuuga();
	if(memory[3] == 0x00000001)
	{
		return 0;
	}
	return 1;
}

//int add_test()
//{
//	int mem[8] =
//		{	0x00401010, 0x4F55AA32, 0xFFFFFFFF, 0x00000005,
//			0x00C01014, 0x00402018, 0x0040101C, 0x00000001
//		};
//	int base_addr = 0;
//	kuuga(mem, base_addr);
//	if(mem[2] == 0x00000004)
//	{
//		return 0;
//	}
//	return 1;
//}
//
//int serial_and_test()
//{
//	uint32 result1 = bit_serial_and(0x00010001, 0x00010000);
//	uint32 result2 = bit_serial_and(0xADD32F10, 0x44E53CD1);
//	uint32 result3 = bit_serial_and(0x10101010, 0x10110001);
//	if (result1 == 0x00010000 && result2 == 0x04C12C10 && result3 == 0x10100000)
//	{
//		return 0;
//	}
//	return 1;
//}
//
//int serial_add_test()
//{
//	uint32 result1 = bit_serial_add(0x0000000A, 0x00000005, false);
//	uint32 result2 = bit_serial_add(0x0000000F, 0x00000005, true);
//	if (result1 == 0x0000000F && result2 == 0x0000000A)
//	{
//		return 0;
//	}
//	return 1;
//}
