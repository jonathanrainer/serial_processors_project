//  *(ram + 0xA8001000/sizeof(int)) = 47;
//	*(ram + base_addr) = base_addr;
//	*(ram + base_addr + 1) = pc;

#include "kuuga.h"

uint32 memory[MEM_SIZE] = {
    0x01406004, 0x01804008, 0x0180600c, 0x00000001,
    0x00000020, 0x00000025, 0x00000000 };
bool zero_flag = false;

uint32 kuuga(int output_loc) {

	uint32 pc = 0;
	uint32 inst = memory[0];
	zero_flag = false;

	// Execute until the halt bit is set.
	main_loop:while (!inst.bit(0))
	{
		uint10 a = ((inst & 0xFFC00000) >> 22);
		uint10 b = ((inst & 0x003FF000) >> 12);
		uint10 c = ((inst & 0x00000FFC) >> 2);
		pc = subleq(pc, a, b, c);
		inst = memory[pc];
	}
	return memory[output_loc];
}

uint32 subleq(uint32 pc, uint10 a, uint10 b,uint10 c)
{
	uint32 m_a = memory[a];
	uint32 m_b = memory[b];
	uint32 check = bit_serial_add(m_b, m_a, true);
	uint32 new_pc  = (check.bit(31) | zero_flag)
		    ? (uint32) c : bit_serial_add(pc,1,false);
	zero_flag = false;
	memory[b] = check;
	return new_pc;
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
