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
	case 0x5:
	  add_constant(operands);
	  pc++;
	  break;
	case 0x6:
	  add_register(operands);
	  pc++;
	  break;
	case 0x7:
	  shift(operands, true, true);
	  pc++;
	  break;
	case 0x8:
	  shift(operands, true, false);
	  pc++;
	  break;
	case 0x9:
	  shift(operands, false, true);
	  pc++;
	  break;
	case 0xA:
	  shift(operands, false, false);
	  pc++;
	  break;
	case 0xB:
	  complement(operands);
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

void add_constant(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
        (uint32) registers[(operands & 0x0003FE00) >> 9],
        operands & 0x000001FF);
}

void add_register(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
      (uint32) registers[(operands & 0x0003FE00) >> 9],
      (uint32) registers[operands & 0x000001FF]);
}

void shift(uint27 operands, bool right_flag, bool arithmetic_flag)
{
  uint32 input = registers[(operands & 0x0003FE00) >> 9];
  uint32 msb = input & 0xC0000000;
  uint32 result = input;
  for(int i = 0; i < (operands & 0x000001FF); i++)
  {
      if (right_flag)
      {
	result = (arithmetic_flag) ? msb | (result >> 1) :
		(result) >> 1;
      }
      else
      {
	result = (result) << 1;
      }
  }
  registers[(operands & 0x07FC0000) >> 18] = result;
}

void complement(uint27 operands)
{
  uint32 input = registers[operands & 0x0003FFFF];
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(~input, 0x1);
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2)
{
  uint32 result = 0x00000000;
  uint1 carry = 0x0;
  add_loop:for (int i = 0; i <= 31; i++)
    {
      uint1 bit_1 = arg1.bit(i);
      uint1 bit_2 = arg2.bit(i);
      result.bit(i) = (bit_1 ^ bit_2 ^ carry);
      carry = (bit_1 & bit_2) | (carry & (bit_1 ^ bit_2));
    }
  return result;
}


