//  *(ram + 0xA8001000/sizeof(int)) = 47;
//	*(ram + base_addr) = base_addr;
//	*(ram + base_addr + 1) = pc;

#include "agito.h"

uint32 registers[10] = {0,0,0,0,0,0,0,0,0,0};

int agito(volatile int * ram, int base_addr) {
  // AXI4 Master Interface
  #pragma HLS INTERFACE ap_bus port=ram bundle=MAXI
  #pragma HLS RESOURCE core=AXI4M variable=ram

  // AXI4 LITE
  #pragma HLS RESOURCE core=AXI4LiteS variable=return metadata="-bus_bundle AXILiteS"

  #pragma HLS INTERFACE ap_none register     port=base_addr
  #pragma HLS RESOURCE core=AXI4LiteS    variable=base_addr metadata="-bus_bundle AXILiteS"

  uint32 pc = 0;
  uint1 halt_flag = false;

  // Execute until the halt bit is set.
  while (!halt_flag)
  {
      uint32 inst = *(ram + base_addr);
      uint5 opcode = inst.getHiBits(5);
      switch (opcode)
      {
	case 0x0000:
	  halt_flag = true;
	  break;
	default :
	  break;
      }
  }
  return 0;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2)
{
  uint32 result = 0x00000000;
  uint1 carry = 0x0;
  add_loop:for (int i = 0; i < 31; i++)
    {
      uint1 bit_1 = arg1.bit(i);
      uint1 bit_2 = arg2.bit(i);
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
