#include "kuuga.h"

int mutation_test();
int subleq_test();
int add_test();

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
	int mem[4] =
	{	0x00803004, 0x00000001, 0x00000004, 0x00000005};
	int pc = 0;
	kuuga(mem, &pc);
	if(mem[3] == 0x00000001)
	{
		return 0;
	}
	return 1;
}

int add_test()
{
	int mem[8] =
		{	0x00401010, 0x4F55AA32, 0x00000004, 0x00000005,
			0x00C01014, 0x00402018, 0x0040101C, 0x00000001
		};
	int pc = 0;
	kuuga(mem, &pc);
	if(mem[2] == 0x00000009)
	{
		return 0;
	}
	return 1;

}
