#include "kuuga.h"
#include <map>
#include <string>
#include <assert.h>

void setUp();
bool mutation_test();
bool subleq_test();
bool add_test();
bool serial_add_test();
bool generated_add_test();
bool generated_sub_test();
bool generated_move_test();
bool generated_not_test();
bool generated_mul_test();
bool generated_div_test();
bool generated_shift_right_test();
bool generated_shift_left_test();
bool generated_and_test();
bool generated_add_mp_test();

int main()
 {
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Mutation Test"] = mutation_test;
  test_funcs["Subleq Test"] = subleq_test;
  test_funcs["Add Test"] = add_test;
  test_funcs["Serial Add Test"] = serial_add_test;
  test_funcs["Generated Add Test"] = generated_add_test;
  test_funcs["Generated Sub Test"] = generated_sub_test;
  test_funcs["Generated MOVE Test"] = generated_move_test;
  test_funcs["Generated NOT Test"] = generated_not_test;
  test_funcs["Generated Multiply Test"] = generated_mul_test;
  test_funcs["Generated Divide Test"] = generated_div_test;
  test_funcs["Generated Shift Right Test"] = generated_shift_right_test;
  test_funcs["Generated Shift Left Test"] = generated_shift_left_test;
  test_funcs["Generated AND Test"] = generated_and_test;
  test_funcs["Fenerated ADD_MP Test"] = generated_add_mp_test;
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
	uint32 result = kuuga(0);
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
		{	0x00401010, 0x4F55AA32, 0xFFFFFFFF, 0xFFFFFFFA,
			0x00C01014, 0x00402018, 0x0040101C, 0x00000001
		};
	setMemory(mem_temp, 8);
	uint32 result = kuuga(2);
	return (result == 0xFFFFFFF9 && memory[3] == 0xFFFFFFFA);
}

bool generated_add_test()
{
	uint32 mem_temp[13] =
	    { 0x01408004, 0x02004008, 0x0200800c, 0x00000001, 0x00000025,
		0x00000032, 0x00000000, 0x00000001, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000 };
	setMemory(mem_temp, 13);
	uint32 result = kuuga(4);
	return (result == 0x00000057 && memory[5] == 0x00000032);
}

bool generated_sub_test()
{
	uint32 mem_temp[11] =
	    { 0x00c02004, 0x00000001, 0x00000025, 0x00000032, 0x00000000,
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000 };
	setMemory(mem_temp, 11);
	uint32 result = kuuga(2);
	return (result == 0xFFFFFFF3 && memory[3] == 0x00000032);
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
	uint32 mem_temp[31] =
	    { 0x0501d004, 0x0741e008, 0x0641900c, 0x0781c010, 0x07019014,
		0x0701c018, 0x0741d01c, 0x0781e020, 0x05819034, 0x04c17028,
		0x05c1a02c, 0x05c17030, 0x05415020, 0x06817038, 0x05c1303c,
		0x05c17040, 0x06419044, 0x0681a048, 0x00000001, 0x00000009,
		0x00000009, 0x00000000, 0x00000001, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000 }
;
	setMemory(mem_temp, 31);
	uint32 result = kuuga(19);
	return (result == 0x51 && memory[20] == 0x9);
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
	return (result == 0x800 && memory[18] == 0x2);
}

bool generated_shift_right_test()
{
	uint32 mem_temp[44] =
	    { 0x07c28004, 0x0a029008, 0x0a82a00c, 0x0a427010, 0x09c2a014,
		0x09c27018, 0x0a02801c, 0x0a429020, 0x08422024, 0x0882a028,
		0x0882202c, 0x0842a074, 0x0ac1e044, 0x08422038, 0x0882503c,
		0x08822040, 0x08020030, 0x0782604c, 0x08020058, 0x08422050,
		0x08825054, 0x08822058, 0x0781e05c, 0x09427060, 0x09c1e064,
		0x09c27068, 0x0942506c, 0x09826070, 0x0802002c, 0x00000001,
		0x00001000, 0x00000008, 0x00000000, 0x00000001, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000002 };
	setMemory(mem_temp, 44);
	uint32 result = kuuga(30);
	return (result == 0x10 && memory[31] == 0x8);
}

bool generated_shift_left_test()
{
  uint32 mem_temp[30] =
      { 0x0481b004, 0x06c1c008, 0x0741d00c, 0x0701a010, 0x0681d014,
	  0x0681a018, 0x06c1b01c, 0x0701c020, 0x05015024, 0x0541d028,
	  0x0541502c, 0x0501d040, 0x04415034, 0x05411038, 0x0541503c,
	  0x04c1302c, 0x00000001, 0x00000001, 0x00000008, 0x00000000,
	  0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }
;
  	setMemory(mem_temp, 30);
  	uint32 result = kuuga(17);
  	return (result == 0x100 && memory[18] == 8);
}

bool generated_and_test()
{
  uint32 mem_temp[87] =
      { 0x1384c004, 0x1304d008, 0x1405000c, 0x1344b010, 0x12c50014,
	  0x12c4b018, 0x1304c01c, 0x1344d020, 0x1104c024, 0x1304d028,
	  0x1585602c, 0x1344b030, 0x12c56034, 0x12c4b038, 0x1304c03c,
	  0x1344d040, 0x118500d8, 0x10c4c048, 0x1304d04c, 0x14451050,
	  0x1344b054, 0x12c51058, 0x12c4b05c, 0x1304c060, 0x1344d064,
	  0x1104c068, 0x1304d06c, 0x14852070, 0x1344b074, 0x12c52078,
	  0x12c4b07c, 0x1304c080, 0x1344d084, 0x14c47088, 0x11c5308c,
	  0x11c47090, 0x13c510c0, 0x13c520cc, 0x1184709c, 0x11c530a0,
	  0x11c470a4, 0x10c470a8, 0x11c430ac, 0x11c470b0, 0x110470b4,
	  0x11c440b8, 0x11c470bc, 0x11445040, 0x150540c4, 0x14454094,
	  0x150540a4, 0x154550d0, 0x14855098, 0x154550a4, 0x10c430dc,
	  0x14c4b0e0, 0x12c430e4, 0x12c4b0e8, 0x110440ec, 0x1584b0f0,
	  0x12c440f4, 0x12c4b0f8, 0x140500fc, 0x14451100, 0x14852104,
	  0x14c53108, 0x00000001, 0x00000c87, 0x0000000f, 0x00000000,
	  0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000021, 0x80000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000 };
  	setMemory(mem_temp, 87);
  	uint32 result = kuuga(67);
  	return (result == 0x7 && memory[68] == 0xF);
}

bool generated_add_mp_test()
{
  uint32 mem_temp[7] =
      { 0x01406004, 0x01804008, 0x0180600c, 0x00000001, 0x00000020,
	  0x00000025, 0x00000000 };
  	setMemory(mem_temp, 7);
  	kuuga(0);
  	return (memory[4] == 0x45 && memory[5] == 0x25);
}

bool serial_add_test()
{
	uint32 result1 = bit_serial_add(0x0000000A, 0x00000005, false);
	uint32 result2 = bit_serial_add(0x0000000F, 0x00000005, true);
	return (result1 == 0x0000000F && result2 == 0x0000000A);
}
