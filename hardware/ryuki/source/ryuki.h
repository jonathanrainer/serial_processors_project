#include <stdio.h>
#include <stdlib.h>
#include <ap_int.h>


typedef ap_uint<32> uint32;
typedef ap_uint<1> uint1;

int ryuki(uint32 * m_addr, uint32 * m_data, uint1 * m_rd, uint1 * m_wr,
	  uint1 * m_rdy, uint1 * mwait, uint32 * mdat);
