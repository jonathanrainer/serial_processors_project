#include "ryuki.h"

uint32 memory[8] = {0xFFFFFFFF, 0x77665544, 0xFFFFFFFF, 0x77665544,
    0xFFFFFFFF, 0x77665544, 0xFFFFFFFF, 0x77665544};

void ryuki(uint32 * output)
{

  *output = memory[4];

  return;
}
