#include <stdio.h>
#include <string.h>
#include "xkuuga.h"
#include "xbasic_types.h"
#include "xparameters.h"

int main() {
    xil_printf("Hello! Setting Up Program!\n\r");
    u32 program[5] = {
    		0x00803004, 0x000000001, 0x00009000,
    		0x00008000, 0x00007000};
    memcpy(0xA8100000, program, 5*sizeof(u32));
    xil_printf("Before Hardware: 0x%X\n", (int) *((volatile int *) 0xA8100008));
    XKuuga instance;
    XKuuga * instance_pointer = &instance;
    XKuuga_Initialize(instance_pointer, 0);
    XKuuga_SetBase_addr(instance_pointer, (0xA8100000/sizeof(int)));
    XKuuga_Start(instance_pointer);
    while(!XKuuga_IsDone(instance_pointer))
    {
    	xil_printf("Stalling....\n");
    }
    int value_2 = *((volatile int *) 0xA8100008);
    xil_printf("After Hardware: 0x%X\n", value_2);
    xil_printf("Finished Communicating with Processor!");
    return 0;
}
