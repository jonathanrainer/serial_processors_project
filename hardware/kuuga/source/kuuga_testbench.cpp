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
bool generated_add_test();
bool generated_sub_test();
bool generated_move_test();
bool generated_not_test();
bool generated_mul_test();
bool generated_div_test();
bool generated_shift_right_test();
bool generated_shift_left_test();

int main()
 {
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Mutation Test"] = mutation_test;
  test_funcs["Subleq Test"] = subleq_test;
  test_funcs["Add Test"] = add_test;
  test_funcs["Serial AND Test"] = serial_and_test;
  test_funcs["Serial Add Test"] = serial_add_test;
  test_funcs["Generated Add Test"] = generated_add_test;
  test_funcs["Generated Sub Test"] = generated_sub_test;
  test_funcs["Generated MOVE Test"] = generated_move_test;
  test_funcs["Generated NOT Test"] = generated_not_test;
  test_funcs["Generated Multiply Test"] = generated_mul_test;
  test_funcs["Generated Divide Test"] = generated_div_test;
  test_funcs["Generated Shift Right Test"] = generated_shift_right_test;
  //test_funcs["Generated Shift Left Test"] = generated_shift_left_test;
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
	  printf("Test #%d: %s - Test Passed!\n", tests,
		 iterator->first.c_str());
	  passes++;
	}
      else
	{
	  printf("Test #d: %s - Test Failed!\n", tests,
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
	uint128 result = kuuga(0);
	return (result == 0x0ABBCFF1);
}

bool subleq_test()
{
	uint32 mem_temp[4] = {
	     0x00803004, 0x00000001, 0x00000004, 0x00000005
	};
	setMemory(mem_temp, 4);
	uint32 result = kuuga(3);
	return (result == 0x00000001);
}

bool add_test()
{
	uint32 mem_temp[8] =
		{	0x00401010, 0x4F55AA32, 0xFFFFFFFF, 0x00000005,
			0x00C01014, 0x00402018, 0x0040101C, 0x00000001
		};
	setMemory(mem_temp, 8);
	uint32 result = kuuga(2);
	return (result == 0x00000004);
}

bool generated_add_test()
{
	uint32 mem_temp[13] =
	    { 0x01408004, 0x02004008, 0x0200800c, 0x00000001, 0x00000025,
		0x00000032, 0x00000000, 0x00000001, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000 };
	setMemory(mem_temp, 13);
	uint32 result = kuuga(4);
	return (result == 0x00000057);
}

bool generated_sub_test()
{
	uint32 mem_temp[11] =
	    { 0x00c02004, 0x00000001, 0x00000025, 0x00000032, 0x00000000,
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000 };
	setMemory(mem_temp, 11);
	uint32 result = kuuga(2);
	return (result == 0xFFFFFFF3);
}

bool generated_move_test()
{
	uint32 mem_temp[14] =
	    { 0x01405004, 0x0180d008, 0x0340500c, 0x0340d010, 0x00000001,
		0x00000025, 0x00000032, 0x00000000, 0x00000001, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	setMemory(mem_temp, 14);
	uint32 result = kuuga(5);
	return (result == 0x00000032);
}

bool generated_not_test()
{
	uint32 mem_temp[16] =
	    { 0x0200c004, 0x0280c008, 0x0200800c, 0x0300f010, 0x03c08014,
		0x03c0f018, 0x0300c01c, 0x00000001, 0x00000025, 0x00000000,
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000 };
	setMemory(mem_temp, 16);
	uint32 result = kuuga(8);
	return (result == 0xFFFFFFDA);
}

bool generated_mul_test()
{
	uint32 mem_temp[19] =
	    { 0x0340b014, 0x0280e008, 0x0381000c, 0x0380e010, 0x0300c000,
		0x0400e018, 0x0380a01c, 0x0380e020, 0x04010024, 0x00000001,
		0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000 };
	setMemory(mem_temp, 19);
	uint32 result = kuuga(10);
	return (result == 0x2);
}

bool generated_div_test()
{
	uint32 mem_temp[27] =
	    { 0x04811014, 0x05015008, 0x0541800c, 0x05415010, 0x04c13000,
		0x0441901c, 0x04c13028, 0x05015020, 0x05418024, 0x05415028,
		0x0441102c, 0x0601a030, 0x06811034, 0x0681a038, 0x0601803c,
		0x06419040, 0x00000001, 0x00001001, 0x00000002, 0x00000000,
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000 };
	setMemory(mem_temp, 27);
	uint32 result = kuuga(17);
	return (result == 0x800);
}

bool generated_shift_right_test()
{
	uint32 mem_temp[33] =
	    { 0x0641b004, 0x06c17008, 0x06c1b00c, 0x06417054, 0x06816024,
		0x0641b018, 0x06c1e01c, 0x06c1b020, 0x06018010, 0x0581f02c,
		0x06018038, 0x0641b030, 0x06c1e034, 0x06c1b038, 0x0581603c,
		0x07820040, 0x08016044, 0x08020048, 0x0781e04c, 0x07c1f050,
		0x0601800c, 0x00000001, 0x00001000, 0x00000008, 0x00000000,
		0x00000001, 0x00000002, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000 };
	setMemory(mem_temp, 30);
	uint32 result = kuuga(22);
	return (result == 0x10);
}

bool generated_shift_left_test()
{
  uint32 mem_temp[27] =
      { 0x04815004, 0x05410008, 0x0541500c, 0x04810038, 0x04813024,
	  0x03c15018, 0x0541701c, 0x05415020, 0x04411010, 0x05c15028,
	  0x0540f02c, 0x05415030, 0x05c17034, 0x0441100c, 0x00000001,
	  0x00000001, 0x00000008, 0x00000000, 0x00000001, 0x00000002,
	  0x80000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000 };
  	setMemory(mem_temp, 27);
  	uint32 result = kuuga(15);
  	printf("Result: %X\n", (int) result);
  	fflush(stdout);
  	return (result == 0x100);
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
