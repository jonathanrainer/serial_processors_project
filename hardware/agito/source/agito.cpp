#include "agito.h"

uint32 registers[REG_NUM] = {0,0,0,0,0,0,0,0,0,0};
uint32 memory[MEM_SIZE] = {0,0,0,0,0,0,0,0};
bool halt_flag = false;
bool zero_flag = false;
uint32 pc = 0;

uint32 agito(int output_loc) {

  halt_flag = false;
  pc = 0;
  uint32 inst;
  // Execute until the halt bit is set.
  main_loop: while (!halt_flag)
  {
      zero_flag = false;
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
	case 0xC:
	  pc = conditional_branch(operands, false, -1, pc);
	  break;
	case 0xD:
	  pc = conditional_branch(operands, true, -1, pc);
	  break;
	case 0xE:
	  pc = conditional_branch(operands, false, 0, pc);
	  break;
	case 0xF:
	  pc = conditional_branch(operands, true, 0, pc);
	  break;
	case 0x10:
	  pc = conditional_branch(operands, false, 1, pc);
	  break;
	case 0x11:
	  pc = conditional_branch(operands, true, 1, pc);
	  break;
	case 0x12:
	  pc = unconditional_branch(operands, false);
	  break;
	case 0x13:
	  pc = unconditional_branch(operands, true);
	  break;
	case 0x14:
	  and_register(operands);
	  pc++;
	  break;
	case 0x15:
	  and_constant(operands);
	  pc++;
	  break;
	case 0x16:
	  or_register(operands);
	  pc++;
	  break;
	case 0x17:
	  or_constant(operands);
	  pc++;
	  break;
	case 0x18:
	  not_register(operands);
	  pc++;
	  break;
	default :
	  break;
      }
  }
  return memory[output_loc];
}

void load_direct(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = memory[operands & 0x0003FFFF];
}

void load_register_offset(uint27 operands)
{
  uint32 memory_location = bit_serial_add(
      registers[(operands & 0x0003FE00) >> 9], operands & 0x000001FF, false);
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
      (uint32) (operands & 0x0003FE00) >> 9, false);
  memory[memory_location] = registers[(operands & 0x000001FF)];
}

void add_constant(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
        (uint32) registers[(operands & 0x0003FE00) >> 9],
        operands & 0x000001FF, false);
}

void add_register(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
      (uint32) registers[(operands & 0x0003FE00) >> 9],
      (uint32) registers[operands & 0x000001FF], false);
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
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(~input, 0x1, false);
}

uint32 conditional_branch(uint27 operands, bool direct_switch,
			  int comparison, uint32 old_pc)
{
  uint32 destination  = (direct_switch) ?
      (uint32) (operands & 0x07FC0000) >> 18 :
      (uint32) registers[(operands & 0x07FC0000) >> 18];
  uint32 result = bit_serial_add(
      (uint32) registers[(operands & 0x0003FE00) >> 9],
      (uint32) registers[(operands & 0x000001FF)], true);
  switch (comparison)
  {
    case -1:
      return (result.bit(31) == 1) ? destination : (uint32) (old_pc+1);
    case 0:
      return (zero_flag) ? destination : (uint32) (old_pc+1);
    default:
      return (!zero_flag &&  (result.bit(31) != 1)) ? destination :
	  (uint32) (old_pc+1);
  }
}

uint32 unconditional_branch(uint27 operands, bool direct_switch)
{
  return (direct_switch) ?
        (uint32) (operands & 0x07FFFFFF):
        (uint32) (registers[(operands & 0x07FC0000) >> 18] +
	(operands & 0x0003FFFF));
}

void and_register(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_and(
          (uint32) registers[(operands & 0x0003FE00) >> 9],
	  (uint32) registers[(operands & 0x000001FF)]);
  return;
}

void and_constant(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_and(
            (uint32) registers[(operands & 0x0003FE00) >> 9],
  	  operands & 0x000001FF);
  return;
}

void or_register(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_or(
          (uint32) registers[(operands & 0x0003FE00) >> 9],
	  (uint32) registers[(operands & 0x000001FF)]);
  return;
}

void or_constant(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_or(
            (uint32) registers[(operands & 0x0003FE00) >> 9],
  	  operands & 0x000001FF);
  return;
}

void not_register(uint27 operands)
{
  registers[(operands & 0x07FC0000) >> 18] = bit_serial_not(
      (uint32) registers[(operands & 0x0003FFFF)]);
}

uint32 bit_serial_and(uint32 arg1, uint32 arg2)
{
  uint32 result = 0x00000000;
  and_loop:for (int i = 0; i <= 31; i++)
  {
    uint1 bit_1 = arg1.bit(i);
    uint1 bit_2 = arg2.bit(i);
    result.bit(i) = (bit_1 & bit_2);
  }
  return result;
}

uint32 bit_serial_or(uint32 arg1, uint32 arg2)
{
  uint32 result = 0x00000000;
  and_loop:for (int i = 0; i <= 31; i++)
  {
    uint1 bit_1 = arg1.bit(i);
    uint1 bit_2 = arg2.bit(i);
    result.bit(i) = (bit_1 | bit_2);
  }
  return result;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag)
{
  uint32 result = 0x00000000;
  uint1 carry = sub_flag;
  bool is_zero = sub_flag;
  add_loop:for (int i = 0; i <= 31; i++)
  {
    uint1 bit_1 = arg1.bit(i);
    uint1 bit_2 = (sub_flag) ? ~arg2.bit(i) : arg2.bit(i);
    uint1 new_bit = (bit_1 ^ bit_2 ^ carry);
    result.bit(i) = new_bit;
    is_zero = (is_zero & !new_bit);
    carry = (bit_1 & bit_2) | (carry & (bit_1 ^ bit_2));
  }
  zero_flag = is_zero;
  return result;
}

uint32 bit_serial_not(uint32 arg)
{
  uint32 result = 0x00000000;
  for(int i = 0; i <= 31; i++)
  {
    result.bit(i) = ~arg.bit(i);
  }
  return result;
}
