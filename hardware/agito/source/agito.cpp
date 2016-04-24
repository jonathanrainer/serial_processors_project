/* Include the header file for access to constants, global variables and 
 * typedefs.
 */
#include "agito.h"

// Set the initial contents of the registers
uint32 registers[REG_NUM] = {0x00000020,0x00000025,0,0,0,0,0,0,0,0};
// Set the initial contents of memory
uint32 memory[MEM_SIZE] = { 0x30000001, 0x00000000 };
// Set the global flags and the program counter
bool halt_flag = false;
bool zero_flag = false;
uint32 pc = 0;

uint32 agito(int output_loc) {
	// Initialise the HALT flag to false and the program counter to 0
	halt_flag = false;
	pc = 0;
	// Execute until the halt bit is set.
	main_loop: while (!halt_flag)
	{
		// Set a new value to the zero flag for every new instruction
		zero_flag = false;
		// Fetch an instructin from memory
		uint32 inst = memory[pc];
		// Split the instruction into its opcode and operands
		uint5 opcode = inst >> 27;
		uint27 operands = inst;
		// Set a status indicator as to whether a branch event has occured or not.
		bool branched = false;
		switch (opcode)
		{
			case 0x0:
				// HALT - Simply stop the processor executing
				halt_flag = true;
				break;
			case 0x1:
				// LOAD - Load a value from memory
				load_direct(operands);
				break;
			case 0x2:
				// LOADRO - Load a value from memory using a pointer and an offset.
				load_register_offset(operands);
				break;
			case 0x3:
				// STORE - Store a value from registers into memory
				store_direct(operands);
				break;
			case 0x4:
				/* 
				 * STORERO - Store a value from registers to memory using a pointer
				 * and an offset
				 */ 
				store_register_offset(operands);
				break;
			case 0x5:
				// ADDC - Add a constant to a value stored in a register
				add_constant(operands);
				break;
			case 0x6:
				// ADD - Add a value in a register to another stored in a register.
				add_register(operands);
				break;
			case 0x7:
				// ASHR - Shift the given register to the right, duplicating the MSB
				shift(operands, true, true);
				break;
			case 0x8:
				// SHR - Shift the given register to the right, pad with zeroes
				shift(operands, true, false);
				break;
			case 0x9:
				// ASHL =-Shift the given register to the left, duplicating the MSB
				shift(operands, false, true);
				break;
			case 0xA:
				// SHL - Shift the given register to the left, pad with zeroes
				shift(operands, false, false);
				break;
			case 0xB:
				// COMP - Create the 2's Complement of a value stored in a register.
				complement(operands);
				break;
			case 0xC:
				/* BLTR - Branch if two registers have a negative difference 
				 * to an address stored in a register.
				 */
				pc = conditional_branch(operands, false, -1, pc);
				branched = true;
				break;
			case 0xD:
				/* BLTR - Branch if two registers have a negative difference, 
				 * to an address stored in a register.
				 */
				pc = conditional_branch(operands, true, -1, pc);
				branched = true;
				break;
			case 0xE::
				/* BER - Branch if two registers have a 0 difference, to an address 
				 * stored in a register.
				 */
				pc = conditional_branch(operands, false, 0, pc);
				branched = true;
				break;
			case 0xF
				/* BEA - Branch if two registers have a 0 difference, to an address 
				 * given in the instruction.
				 */
				pc = conditional_branch(operands, true, 0, pc);
				branched = true;
				break;
			case 0x10:
				/* BGTR - Branch if two registers have a positive difference, to an
				 * address stored in a register.
				 */
				pc = conditional_branch(operands, false, 1, pc);
				branched = true;
				break;
			case 0x11:
				/* BGTA - Branch if two registers have a positive difference, to an
				 * address stored in the instruction itself.
				 */
				pc = conditional_branch(operands, true, 1, pc);
				branched = true;
				break;
			case 0x12:
				/* BRO - Unconditionally branch to an address given by a register
				 * and an offset.
				 */
				pc = unconditional_branch(operands, false);
				branched = true;
				break;
			case 0x13:
				/* BA - Unconditionally branch to an address given in the 
				 * instruction.
				 */
				pc = unconditional_branch(operands, true);
				branched = true;
				break;
			case 0x14:
				// AND - Take the bitwise AND of two registers.
				and_register(operands);
				break;
			case 0x15:
				// ANDC - Take the bitwise AND of a register and a constant.
				and_constant(operands);
				break;
			case 0x16:
				// OR - Take the bitwise OR of two registers.
				or_register(operands);
				break;
			case 0x17:
				// ORC - Take the bitise OR of a register and a constant.
				or_constant(operands);
				break;
			case 0x18:
				// NOT - Calculate the bitwise NOT (1's Complement) of a register.
				not_register(operands);
				break;
			default :
				// If any unknown opcodes are recieved just ignore them and move on.
				break;
		}
		/* If a branch has occurred then don't change the program counter, 
		 * otherwise, increment it. 
		 */ 
		pc = (branched) ? pc : bit_serial_add(pc, 1, false);
	}
	// Return the specified register to ensure the correct operation
	return registers[output_loc];
}

void load_direct(uint27 operands)
{
	/* Extract the operands and copy the memory location into the specified
	 * register.
	 */
	registers[(operands & 0x07FC0000) >> 18] = memory[operands & 0x0003FFFF];
}

void load_register_offset(uint27 operands)
{
	// Calculate the source memory location by adding the pointer and offset.
	uint32 memory_location = bit_serial_add(
		registers[(operands & 0x0003FE00) >> 9], operands & 0x000001FF, false);
	// Perform the LOAD from memory.
	registers[(operands & 0x07FC0000) >> 18] = memory[memory_location];
}

void store_direct(uint27 operands)
{
	// Store the given registers value directly into memory.
	memory[(operands & 0x7FFFE00) >> 9] = registers[(operands & 0x000001FF)];
}

void store_register_offset(uint27 operands)
{
	// Calculate the destination address by adding pointer and offset.
	uint32 memory_location = bit_serial_add(
		(uint32) registers[(operands & 0x07FC0000) >> 18],
		(uint32) (operands & 0x0003FE00) >> 9, false);
	// Store the register value into the calculated memory location.
	memory[memory_location] = registers[(operands & 0x000001FF)];
}

void add_constant(uint27 operands)
{
	// Calculate, and store, the value of the register and constant.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		operands & 0x000001FF, false);
}

void add_register(uint27 operands)
{
	// Add together the two register values and store it into the third register.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		(uint32) registers[operands & 0x000001FF], false);
}

void shift(uint27 operands, bool right_flag, bool arithmetic_flag)
{
	// Extract the input from the source register
	uint32 input = registers[(operands & 0x0003FE00) >> 9];
	// Extract the most significant bit, with all necessary trailing zeroes.
	uint32 msb = input & 0xC0000000;
	// Set the result to be the input initially
	uint32 result = input;
	// Iterate over each bit
	shift_loop:for(int i = 0; i < (operands & 0x000001FF); i++)
	{
		// If shifting right
		if (right_flag)
		{
			// Check if you need to duplicate the MSB or just add on a 0
			result = (arithmetic_flag) ? msb | (result >> 1) : (result) >> 1;
		}
		// Otherwise you can only be shifting left.
		else
		{
			// Perform the usual shift operation
			result = (result) << 1;
		}
	}
	// Store the result to the destination register.
	registers[(operands & 0x07FC0000) >> 18] = result;
}

void complement(uint27 operands)
{
	// Extract the input from the registers
	uint32 input = registers[operands & 0x0003FFFF];
	// Negate the input and then add 1 (2's complement conversion)
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_add(~input, 0x1,
																					false);
}

uint32 conditional_branch(uint27 operands, bool direct_switch,
			  int comparison, uint32 old_pc)
{
	/* Calculate the destination, based on whether it's an address or register
	 * offset based branch.
	 */
	uint32 destination  = (direct_switch) ?
		(uint32) (operands & 0x07FC0000) >> 18 :
		(uint32) registers[(operands & 0x07FC0000) >> 18];
	// Calculate the result of subtracting the two operands as a comparison.
	uint32 result = bit_serial_add(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		(uint32) registers[(operands & 0x000001FF)], true);
	// Based on the type of comparison that is to be made.
	switch (comparison)
	{
		case -1:
			/* Less Than - So operands should have a negative difference.
			 * Consequently the sign bit of the result needs to be checked.
			 */
			return (result.bit(31)) ? destination : 
												bit_serial_add(old_pc, 1, false);
		case 0:
			/* Equal To - So operands should have a 0 difference.
			 * Consequently the zero_flag is the only thing to check.
			 */
			return (zero_flag) ? destination : bit_serial_add(old_pc, 1, false);
		default:
			/* Greater Than - So operands should have a positive difference.
			 * Due to the method of construction this is simply the case that
			 * neither of the other two cases are true.
			 */
			return (!(zero_flag ||  result.bit(31))) ? destination :
												bit_serial_add(old_pc, 1, false);
	}
}

uint32 unconditional_branch(uint27 operands, bool direct_switch)
{
	// Branch to either the given address of the address calculated.
	return (direct_switch) ? (uint32) (operands & 0x07FFFFFF):
			(uint32) bit_serial_add(registers[(operands & 0x07FC0000) >> 18],
											(operands & 0x0003FFFF), false);
}

void and_register(uint27 operands)
{
	// Bitwise AND the two registers together and store the result in the third.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_and(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		(uint32) registers[(operands & 0x000001FF)]);
	return;
}

void and_constant(uint27 operands)
{
	// Bitwise AND the given register and constant.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_and(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		operands & 0x000001FF);
	return;
}

void or_register(uint27 operands)
{
	// Bitwise OR the two registers together and store the result in the third.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_or(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		(uint32) registers[(operands & 0x000001FF)]);
  return;
}

void or_constant(uint27 operands)
{
	// Bitwise OR the given register and constant.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_or(
		(uint32) registers[(operands & 0x0003FE00) >> 9],
		operands & 0x000001FF);
	return;
}

void not_register(uint27 operands)
{
	// Calculate the NOT of the given register.
	registers[(operands & 0x07FC0000) >> 18] = bit_serial_not(
		(uint32) registers[(operands & 0x0003FFFF)]);
}

uint32 bit_serial_and(uint32 arg1, uint32 arg2)
{
	// Set the initial result to 0
	uint32 result = 0x00000000;
	// Iterate over each of the bits in turn.
	and_loop:for (int i = 0; i <= 31; i++)
	{
		// Calculate each new bit by bitwise ANDing the two older bits together.
		result.bit(i) = (arg1.bit(i) & arg2.bit(i));
	}
	// Return the final result.
	return result;
}

uint32 bit_serial_or(uint32 arg1, uint32 arg2)
{
	// Set the initial result to 0
	uint32 result = 0x00000000;
	// Iterate through each bit in turn.
	or_loop:for (int i = 0; i <= 31; i++)
	{
		// Calculate the result bit by ORing together to the two old bits.
		result.bit(i) = (arg1.bit(i) | arg2.bit(i));
	}
	// Return the result.
	return result;
}

uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag)
{
	// Set up the result and carry locations to be used throughout the loop
	uint32 result = 0x00000000;
	/* Set the carry bit to the same value (0 or 1) as the sub_flag. 
	 * If a subtraction is being performed then the carry bit will be primed 
	 * with the appropriate value.
	 */
	uint1 carry = sub_flag;
	// Set a flag to indicate if the result generated here is zero
	bool is_zero = sub_flag;
	// Iterate over each bit
	add_loop:for (int i = 0; i <= 31; i++)
	{
		// Negate the second bit if this is a subtraction.
		uint1 bit_2 = (sub_flag) ? ~arg2.bit(i) : arg2.bit(i);
		// XOR the bits together to get the new result bit
		result.bit(i) = (arg1.bit(i) ^ bit_2 ^ carry);
		/* If the new bit is 0 then don't change is_zero otherwise the result 
		 * has a magnitude so it needs altering and then cannot be changed back.
		 */
		is_zero = (is_zero & !result.bit(i));
		// Calculate the carry for the next iteration of the loop
		carry = (arg1.bit(i) & bit_2) | (carry & (arg1.bit(i) ^ bit_2));
	}
	// Set the global zero flag to the state of is_zero
	zero_flag = is_zero;
	// Return the calculated result.
	return result;
}

uint32 bit_serial_not(uint32 arg)
{
	// Set the initial result to 0
	uint32 result = 0x00000000;
	// Iterate over each bit in turn.
	not_loop:for(int i = 0; i <= 31; i++)
	{
		// Negate each bit as it's arrived at.
		result.bit(i) = ~arg.bit(i);
	}
	// Return the result
	return result;
}
