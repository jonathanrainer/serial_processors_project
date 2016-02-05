#include "kuuga.h"

int mutation_test();
int subleq_test();

int main()
{
	return mutation_test() | subleq_test() | add_test();
}

int mutation_test()
{
	int mem[1] = {0x0ABBCFF1};
	int pc = 0;
	kuuga(mem, &pc);
	if(mem[0] == 0x0ABBCFF1)
	{
		return 0;
	}
	return 1;
}

int subleq_test()
{
	int mem[4*sizeof(int)] =
	{	0x0200C000,0x00000000,0x00000000,0x00000000,
		0x00000001,0x00000000,0x00000000,0x00000000,
		0x00000004,0x00000000,0x00000000,0x00000000,
		0x00000005,0x00000000,0x00000000,0x00000000};
	int pc = 0;
	kuuga(mem, &pc);
	if(mem[12] == 0x00000001)
	{
		return 0;
	}
	return 1;
}

int add_test()
{

}
