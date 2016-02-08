#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "xkuuga.h"
#include "xbasic_types.h"
#include "xparameters.h"

int main() {
    xil_printf("Hello! Setting Up Program!\n\r");
    u32 program[7] =
    {
    		0x00C05004, 0x01404008, 0x01405018, 0x00000006,
    		0x00000005, 0x00000000, 0x00000001
    };
    memcpy(0xA8100000, program, 7*sizeof(u32));
    xil_printf("Before Hardware: 0x%X\n", (int) *((volatile int *) 0xA8100010));
    XKuuga instance;
    XKuuga * instance_pointer = &instance;
    XKuuga_Initialize(instance_pointer, 0);
    XKuuga_SetBase_addr(instance_pointer, (0xA8100000/sizeof(int)));
    XKuuga_Start(instance_pointer);
    while(!XKuuga_IsDone(instance_pointer))
    {
    	xil_printf("Working....\n");
    }
    xil_printf("After Hardware: 0x%X\n", *((volatile int *) 0xA8100010));
    xil_printf("Finished Communicating with Processor!");
    return 0;
}
