#include <stdio.h>
#include "xkuuga.h"

int main() {
    xil_printf("Hello! Working on calling Processor!\n\r");
    int value_1 = *((volatile int *) 0xA8001000);
    xil_printf("Before Hardware: %d", value_1);
    XKuuga instance;
    XKuuga * instance_pointer = &instance;
    XKuuga_Initialize(instance_pointer, 0);
    XKuuga_Start(instance_pointer);
    int value_2 = *((volatile int *) 0xA8001000);
    xil_printf("After Hardware: %d", value_2);
    xil_printf("\n\rFinished Communicating with Processor!");
    return 0;
}
