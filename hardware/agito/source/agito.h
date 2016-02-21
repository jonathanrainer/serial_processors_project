#ifndef __TOPLEVEL_H_
#define __TOPLEVEL_H_

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>

//Typedefs
typedef ap_uint<32> uint32;
typedef ap_uint<27> uint27;
typedef ap_uint<10> uint10;
typedef ap_uint<9> uint9;
typedef ap_uint<5> uint5;
typedef ap_uint<1> uint1;

// Prototypes
int agito(volatile int * ram, int base_addr);
void load_direct(uint27 operands, volatile int * ram);
void load_register_offset(uint27 operands, volatile int * ram);
uint32 bit_serial_add(uint32 arg1, uint32 arg2);
//void print_memory(volatile int * ram);

// Globals
extern uint32 registers[10];

#endif
