#include "kuuga.h"
#include <map>
#include <string>
#include <assert.h>

void setUp();
bool mutation_test();
bool subleq_test();
bool add_test();
bool serial_and_test();
bool serial_add_test();

int main()
 {
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Mutation Test"] = mutation_test;
  test_funcs["Subleq Test"] = subleq_test;
  test_funcs["Add Test"] = add_test;
  test_funcs["Serial AND Test"] = serial_and_test;
  test_funcs["Serial ADD Test"] = serial_add_test;
  int passes = 0;
  int fails = 0;
  int tests = 0;
  printf("########## TEST RESULTS ##########\n");
  for(it_type iterator = test_funcs.begin(); iterator != test_funcs.end();
      iterator++)
    {
      tests++;
      setUp();
      if((*(iterator->second))())
	{
	  printf("Test %d#: %s - Test Passed!\n", tests,
		 iterator->first.c_str());
	  passes++;
	}
      else
	{
	  printf("Test #d#: %s - Test Failed!\n", tests,
		 iterator->first.c_str());
	  fails++;
	}
    }
  printf("########## END RESULTS ##########\n");
  printf("Summary - Passes: %d/%d - Fails: %d/%d\n", passes, passes+fails,
	 fails, passes+fails);
  return 0;
}

void setUp()
{
  for(int i = 0; i < MEM_SIZE; i++)
    {
      memory[i] = 0;
    }
}

void setMemory(uint32 * new_mem, int size)
{
  assert(size <= MEM_SIZE);
  for(int i = 0; i < size; i++)
    {
      memory[i] = new_mem[i];
    }
  return;
}

bool mutation_test()
{
	uint32 memory_temp[1] = {0x0ABBCFF1};
	setMemory(memory_temp, 1);
	kuuga();
	return (memory[0] == 0x0ABBCFF1);
}

bool subleq_test()
{
	uint32 mem_temp[4] = {
	     0x00803004, 0x00000001, 0x00000004, 0x00000005
	};
	setMemory(mem_temp, 4);
	kuuga();
	return (memory[3] == 0x00000001);
}

bool add_test()
{
	uint32 mem_temp[8] =
		{	0x00401010, 0x4F55AA32, 0xFFFFFFFF, 0x00000005,
			0x00C01014, 0x00402018, 0x0040101C, 0x00000001
		};
	setMemory(mem_temp, 8);
	kuuga();
	return (memory[2] == 0x00000004);
}

bool serial_and_test()
{
	uint32 result1 = bit_serial_and(0x00010001, 0x00010000);
	uint32 result2 = bit_serial_and(0xADD32F10, 0x44E53CD1);
	uint32 result3 = bit_serial_and(0x10101010, 0x10110001);
	return (result1 == 0x00010000 &&
	    result2 == 0x04C12C10 && result3 == 0x10100000);
}

bool serial_add_test()
{
	uint32 result1 = bit_serial_add(0x0000000A, 0x00000005, false);
	uint32 result2 = bit_serial_add(0x0000000F, 0x00000005, true);
	return (result1 == 0x0000000F && result2 == 0x0000000A);
}
