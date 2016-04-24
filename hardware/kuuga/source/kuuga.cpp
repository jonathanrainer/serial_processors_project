// Include header file for constants and globals.
#include "kuuga.h"

/* Declare memory as a global variable so it can be accessed by all the 
 * functions as necessary. When implemented this will actualy be a BRAM.
 */
uint32 memory[MEM_SIZE];

uint32 kuuga(int output_loc) {

	// Set up program counter and fetch the first instruction from memory
	uint32 pc = 0;
	uint32 inst = memory[pc];
	// Run the loop until the HALT bit is set
	main_loop:while (!inst.bit(0))
	{
		/* Update the program counter by running SUBLEQ on the operands
		 * stored within the instruction
		 */
		pc = subleq(pc,(uint10) (inst >> 22), (uint10) (inst >> 12),
						(uint10) (inst >> 2));
		// Fetch the next instruction to be executed from memory.
		inst = memory[pc];
	}
	/* Report back the contents of memory stored at the given location,
	 * as a method of verifying that the correct operation has been performed.
	 */
	return memory[output_loc];
}

uint32 subleq(uint32 pc, uint10 a, uint10 b,uint10 c)
{
	// Set the Zero flag to true as nothing has as yet happened.
	bool zero_flag = true;
	/* Fetch operands from memory locations a and b and subtract them,
	 * recording the result to be stored back to b and so that if the result is
	 * negative branching can occur.
	 */
	uint32 check = bit_serial_add(memory[b], memory[a], true, &zero_flag);
	/* Calculate the new value of the program counter, branching if the 
	 * Zero Flag is set or the result is negative. Otherwise move on 
	 * sequentially to the next instruction
	*/
	uint32 new_pc  = (check.bit(31) | zero_flag)
							? (uint32) c : bit_serial_add(pc,1,false, &zero_flag);
	// Store check back to memory.
	memory[b] = check;
	// Return the computed value of the new program counter.
	return new_pc;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag, bool * zero_flag)
{
	// Set up the result and carry locations to be used throughout the loop
	uint32 result = 0x00000000;
	/* Set the carry bit to the same value (0 or 1) as the sub_flag.
	 * If a subtraction is being performed then the carry bit will be primed 
	 * with the appropriate value.
	 */
	uint1 carry = sub_flag;
	// Iterate over each bit
	add_loop:for (int i = 0; i <= 31; i++)
	{
		// Negate the second bit if this is a subtraction.
		uint1 bit_2 = (sub_flag) ? ~arg2.bit(i) : arg2.bit(i);
		// XOR the bits together to get the new result bit
		result.bit(i) = (arg1.bit(i) ^ bit_2 ^ carry);
		// Set the value of the zero flag dependent on the new bit just created
		*zero_flag = (*zero_flag & !result.bit(i));
		// Calculate the value of the carry flag for the next loop iteration.
		carry = (arg1.bit(i) & bit_2) | (carry & (arg1.bit(i) ^ bit_2));
	}
	// Return the calculated result.
	return result;
}