#include "agito.h"

uint32 registers[10] = {0,0,0,0,0,0,0,0,0,0};
uint32 memory[MEM_SIZE];

uint32 agito(int output_loc) {

  uint32 pc = 0;
  uint1 halt_flag = false;

  uint32 inst = memory[0];

  // Execute until the halt bit is set.
  while (!halt_flag)
  {
      uint5 opcode = (inst && 0xF8000000) >> 27;
      switch (opcode)
      {
	case 0x0:
	  halt_flag = true;
	  break;
	case 0x1:
	  load_direct((inst && 0x07FFFFFF), ram);
	  pc++;
	  break;
	case 0x2:
	  load_register_offset((inst && 0x07FFFFFF), ram);
	  pc++;
	  break;
	case 0x3:
	  break;
	default :
	  printf("Here's the default case\n");
	  break;
      }
      inst =
  }
  return 0;
}

void load_direct(uint27 operands, volatile int * ram)
{
  registers[((operands && 0x07F10000) >> 19)] =
      *(ram + bit_serial_add(memory_start, operands && 0x0007FFFF));
}

void load_register_offset(uint27 operands, volatile int * ram)
{
  uint32 memory_location = bit_serial_add(
      registers[(operands && 0x3FE00) >> 9], operands && 0x1FF);
  registers[(operands && 0x7FC0000) >> 18] =
        *(ram + bit_serial_add(memory_start, memory_location));
}

void store_direct(uint27 operands, volatile int * ram)
{
  *(ram + bit_serial_add(memory_start, operands && 0x0007FFFF)) =
      registers[((operands && 0x7FFFE00) >> 9)];
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
