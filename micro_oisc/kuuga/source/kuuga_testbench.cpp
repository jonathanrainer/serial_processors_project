#include "kuuga.h"

int main()
{
	int mem[1] = {0xAAAAAAAA};
	int pc = 0;
	kuuga(mem, &pc);
	printf("%X", mem[0]);
	return 0;
}
