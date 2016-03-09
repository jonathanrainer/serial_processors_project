#include "agito.h"

uint32 registers[REG_NUM] = {0,0,0,0,0,0,0,0,0,0};
uint32 memory[MEM_SIZE] = {0,0,0,0,0,0,0,0};

uint32 agito(int output_loc) {

  uint32 pc = 0;
  bool halt_flag = false;

  uint32 inst;

  // Execute until the halt bit is set.
  while (!halt_flag)
  {
      inst = memory[pc];
      uint5 opcode = (inst & 0xF8000000) >> 27;
      uint27 operands = (inst & 0x07FFFFFF);
      switch (opcode)
      {
	case 0x0:
	  halt_flag = true;
	  break;
	case 0x1:
	  load_direct(operands);
	  pc++;
	  break;
	case 0x2:
	  load_register_offset(operands);
	  pc++;
	  break;
	case 0x3:
	  store_direct(operands);
	  pc++;
	  break;
	case 0x4:
	  store_register_offset(operands);
	  pc++;
	  break;
	case 0x6:
	  add_register(operands);
	  pc++;
	  break;
	default :
	  break;
      }
  }
  return 0;
}

void load_direct(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = memory[operands & 0x0003FFFF];
}

void load_register_offset(uint27 operands)
{
  uint32 memory_location = bit_serial_add(
      registers[(operands & 0x0003FE00) >> 9], operands & 0x000001FF);
  registers[(operands & 0x07FC0000) >> 18] = memory[memory_location];
}

void store_direct(uint27 operands)
{
  memory[(operands & 0x7FFFE00) >> 9] = registers[(operands & 0x000001FF)];
}

void store_register_offset(uint27 operands)
{
  uint32 memory_location = bit_serial_add(
      (uint32) registers[(operands & 0x07FC0000) >> 18],
      (uint32) (operands & 0x0003FE00) >> 9);
  memory[memory_location] = registers[(operands & 0x000001FF)];
}

void add_register(uint27 operands)
{
  registers[operands & 0x000001FF] = bit_serial_add(
      (uint32) registers[(operands & 0x07FC0000) >> 18],
      (uint32) registers[(operands & 0x0003FE00) >> 9]);
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
