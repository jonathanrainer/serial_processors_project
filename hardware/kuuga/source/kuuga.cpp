#include "kuuga.h"

uint32 memory[MEM_SIZE] = {
    0x01406004, 0x01804008, 0x0180600c, 0x00000001,
    0x00000020, 0x00000025, 0x00000000 };

uint32 kuuga(int output_loc) {

	uint32 pc = 0;
	uint32 inst = memory[pc];

	// Execute until the halt bit is set.
	main_loop:while (!inst.bit(0))
	{
		pc = subleq(pc,(uint10) (inst >> 22), (uint10) (inst >> 12),
			     (uint10) (inst >> 2));
		inst = memory[pc];
	}
	return memory[output_loc];
}

uint32 subleq(uint32 pc, uint10 a, uint10 b,uint10 c)
{
	bool zero_flag = true;
	uint32 check = bit_serial_add(memory[b], memory[a], true, &zero_flag);
	uint32 new_pc  = (check.bit(31) | zero_flag)
		    ? (uint32) c : bit_serial_add(pc,1,false, &zero_flag);
	memory[b] = check;
	return new_pc;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag, bool * zero_flag)
{
	uint32 result = 0x00000000;
	uint1 carry = sub_flag;
	add_loop:for (int i = 0; i <= 31; i++)
	{
	    uint1 bit_2 = (sub_flag) ? ~arg2.bit(i) : arg2.bit(i);
	    result.bit(i) = (arg1.bit(i) ^ bit_2 ^ carry);
	    *zero_flag = (*zero_flag & !result.bit(i));
	    carry = (arg1.bit(i) & bit_2) | (carry & (arg1.bit(i) ^ bit_2));
	}
	return result;
}
