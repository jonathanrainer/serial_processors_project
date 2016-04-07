#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>

//Typedefs
typedef ap_uint<32> uint32;
typedef ap_uint<27> uint27;
typedef ap_uint<18> uint18;
typedef ap_uint<10> uint10;
typedef ap_uint<9> uint9;
typedef ap_uint<5> uint5;
typedef ap_uint<1> uint1;

// Prototypes
uint32 agito(int output_loc);
void load_direct(uint27 operands);
void load_register_offset(uint27 operands);
uint32 bit_serial_add(uint32 arg1, uint32 arg2, bool sub_flag);
void store_direct(uint27 operands);
void store_register_offset(uint27 operands);
void add_register(uint27 operands);
void add_constant(uint27 operands);
void shift(uint27 operands, bool right_flag, bool arithmetic_flag);
void complement(uint27 operands);
uint32 conditional_branch(uint27 operands, bool direct_switch,
			  int comparison, uint32 old_pc);
uint32 unconditional_branch(uint27 operands, bool direct_switch);
uint32 bit_serial_and(uint32 arg1, uint32 arg2);
void and_constant(uint27 operands);
void and_register(uint27 operands);
uint32 bit_serial_or(uint32 arg1, uint32 arg2);
void or_constant(uint27 operands);
void or_register(uint27 operands);
void not_register(uint27 operands);
uint32 bit_serial_not(uint32 arg);

// Defines
#define MEM_SIZE 30
#define REG_NUM 11

// Globals
extern uint32 memory[MEM_SIZE];
extern uint32 registers[REG_NUM];

#endif
