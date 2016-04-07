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
bool generated_atoi_test();
bool generated_divu_test();
bool generated_asl64_test();
bool generated_rem_test();
bool generated_copy_test();
bool generated_copy_test();
bool generated_fprintf_test();
bool generated_int64eq_test();
bool generated_asr64_test();
bool generated_utsa_var_args_test();
bool generated_add64_test();

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
  test_funcs["Generated ADD_MP Test"] = generated_add_mp_test;
  test_funcs["Generated ATOI Test"] = generated_atoi_test;
  test_funcs["Generated DIVU Test"] = generated_divu_test;
  test_funcs["Generated ASL64 Test"] = generated_asl64_test;
  test_funcs["Generated REM Test"] = generated_rem_test;
  test_funcs["Generated COPY Test"] = generated_copy_test;
  test_funcs["Generated FPRINTF Test"] = generated_fprintf_test;
  test_funcs["Generated INT64EQ Test"] = generated_int64eq_test;
  test_funcs["Generated ASR64 Test"] = generated_asr64_test;
  test_funcs["Generated UTSA VA ARGS Test"] = generated_utsa_var_args_test;
  test_funcs["Generated ADD64 Test"] = generated_add64_test;
  int passes = 0;
  int fails = 0;
  int tests = 0;
  printf("########## TEST RESULTS ##########\n");
  fflush(stdout);
  for(it_type iterator = test_funcs.begin(); iterator != test_funcs.end();
      iterator++)
    {
      tests++;
      setUp();
      if((*(iterator->second))())
	{
	  printf("Test #%d: %s - Test Passed!\n", tests,
		 iterator->first.c_str());
	  fflush(stdout);
	  passes++;
	}
      else
	{
	  printf("Test #d: %s - Test Failed!\n", tests,
		 iterator->first.c_str());
	  fflush(stdout);
	  fails++;
	}
    }
  printf("########## END RESULTS ##########\n");
  printf("Summary - Passes: %d/%d - Fails: %d/%d\n", passes, passes+fails,
	 fails, passes+fails);
  fflush(stdout);
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
	    { 0x00c02004, 0x00000001, 0x000000054, 0x00000032, 0x00000000,
		0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000 };
	setMemory(mem_temp, 11);
	uint32 result = kuuga(2);
	return (result == 0x22 && memory[3] == 0x00000032);
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
	  0x14c53108, 0x00000001, 0xCFFFFFFF, 0x0000025F, 0x00000000,
	  0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000021, 0x80000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000 };
  	setMemory(mem_temp, 87);
  	uint32 result = kuuga(67);
  	return (result == 0x25F && memory[68] == 0x25F);
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

bool generated_atoi_test()
{
  uint32 mem_temp[9] =
      { 0x01c08004, 0x02004008, 0x0200800c, 0x00000001, 0x00000050,
	  0x00000020, 0x00000025, 0x00000010, 0x00000000 };
  	setMemory(mem_temp, 9);
  	kuuga(0);
  	return (memory[4] == 0x60 && memory[7] == 0x10);
}

bool generated_divu_test()
{
  uint32 mem_temp[7] =
      { 0x01805004, 0x00000001, 0x00000010, 0x00000025, 0x00000007,
	  0x80000000, 0x00000001 };
  	setMemory(mem_temp, 7);
  	kuuga(0);
  	return (memory[5] == 0x7FFFFFFF && memory[6] == 0x1);
}

bool generated_asl64_test()
{
  uint32 mem_temp[18] =
      { 0x0380f004, 0x03c10008, 0x0340d00c, 0x04011010, 0x0440d014,
	  0x04411018, 0x03c0f01c, 0x04010020, 0x02c0d024, 0x00000001,
	  0x00000025, 0x00000004, 0x00000013, 0x00000000, 0x00000020,
	  0x00000000, 0x00000000, 0x00000000 };
  	setMemory(mem_temp, 18);
  	kuuga(0);
  	return (memory[13] == 0x1C && memory[11] == 0x4);
}

bool generated_rem_test()
{
  uint32 mem_temp[60] =
      { 0x0b034004, 0x0d035008, 0x0c03000c, 0x0d436010, 0x0d830014,
	  0x0d836018, 0x0d03401c, 0x0d435020, 0x0b430034, 0x0c837028,
	  0x0dc3802c, 0x0dc37030, 0x0cc33020, 0x0c03903c, 0x0cc33048,
	  0x0c837040, 0x0dc38044, 0x0dc37048, 0x0c03004c, 0x0e036050,
	  0x0d830054, 0x0d836058, 0x0e03805c, 0x0e439060, 0x0b034064,
	  0x0d035068, 0x0e83a06c, 0x0d436070, 0x0d83a074, 0x0d836078,
	  0x0d03407c, 0x0d435080, 0x0c83a094, 0x0c037088, 0x0dc3b08c,
	  0x0dc37090, 0x0cc33080, 0x0ec37098, 0x0dc3009c, 0x0dc370a0,
	  0x0e83a0a4, 0x0ec3b0a8, 0x0b4300ac, 0x00000001, 0x00000008,
	  0x00000002, 0x00000065, 0x00000010, 0x00000000, 0x00000000,
	  0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
  	setMemory(mem_temp, 60);
  	kuuga(0);
  	return (memory[48] == 0x1E);
}

bool generated_copy_test()
{
  uint32 mem_temp[13] =
      { 0x0240b004, 0x02c0a008, 0x02c0b00c, 0x03006010, 0x00000001,
	  0x00000006, 0x00000007, 0x00000010, 0x00000050, 0x0000000c,
	  0x00000050, 0x00000000, 0x00000001 };
  setMemory(mem_temp, 13);
  kuuga(0);
  return (memory[6] == 0x6);

}

bool generated_fprintf_test()
{
  uint32 mem_temp[16] =
      { 0x02c0e004, 0x0380d008, 0x0380e00c, 0x02008010, 0x0300e014,
	  0x03809018, 0x0380e01c, 0x00000001, 0x00000005, 0x0000000b,
	  0x00000aaa, 0x00000008, 0x00000004, 0x00000050, 0x00000000,
	  0x00000001 };
  setMemory(mem_temp, 16);
  kuuga(0);
  return (memory[9] == 0xF);

}

bool generated_int64eq_test()
{
  uint32 mem_temp[16] =
      { 0x01809004, 0x02408008, 0x0240900c, 0x00000001, 0x0000000a,
	  0x0000000b, 0x0000000c, 0x00000567, 0xFFFFFFF7, 0x00000000 };
  setMemory(mem_temp, 10);
  kuuga(0);
  return (memory[8] == 0x3);

}

bool generated_asr64_test()
{
  uint32 mem_temp[93] =
      { 0x12c57004, 0x15c4a008, 0x15c5700c, 0x13858010, 0x16059014,
	  0x14050018, 0x1645a01c, 0x16850020, 0x1685a024, 0x16058028,
	  0x1645902c, 0x13058030, 0x16059034, 0x15856038, 0x1645a03c,
	  0x16856040, 0x1685a044, 0x16058048, 0x1645904c, 0x16c500e4,
	  0x12058054, 0x16059058, 0x1445105c, 0x1645a060, 0x16851064,
	  0x1685a068, 0x1605806c, 0x16459070, 0x13058074, 0x16059078,
	  0x1485207c, 0x1645a080, 0x16852084, 0x1685a088, 0x1605808c,
	  0x16459090, 0x14c57094, 0x15c53098, 0x15c5709c, 0x13c510cc,
	  0x13c520d8, 0x16c570a8, 0x15c530ac, 0x15c570b0, 0x120570b4,
	  0x15c480b8, 0x15c570bc, 0x130570c0, 0x15c4c0c4, 0x15c570c8,
	  0x1705c04c, 0x150540d0, 0x144540a0, 0x150540b0, 0x154550dc,
	  0x148550a4, 0x154550b0, 0x120480e8, 0x14c5a0ec, 0x168480f0,
	  0x1685a0f4, 0x1304c0f8, 0x1585a0fc, 0x1684c100, 0x1685a104,
	  0x14050108, 0x1445110c, 0x14852110, 0x14c53114, 0x00000001,
	  0x00000014, 0x00000022, 0x00000055, 0x00000750, 0x00000050,
	  0x00000008, 0x0000003f, 0x0000001F, 0x00000021, 0x80000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000001, 0x00000000 };
  setMemory(mem_temp, 93);
  kuuga(0);
  return (memory[72] == 0x15);

}

bool generated_utsa_var_args_test()
{
  uint32 mem_temp[15] =
      { 0x0240c004, 0x0300e008, 0x0380c00c, 0x0380e010, 0x0300e014,
	  0x0380c018, 0x0380e01c, 0x0280c020, 0x00000001, 0x00000010,
	  0x00000020, 0x00000079, 0x00000004, 0x00000002, 0x00000000 };
  setMemory(mem_temp, 15);
  kuuga(0);
  return (memory[12] == 0xFFFFFFB0);
}

bool generated_add64_test()
{
  uint32 mem_temp[176] =
      { 0x2609e004, 0x2789a008, 0x2789e00c, 0x2489e010, 0x27895014,
	  0x2789e018, 0x2509e01c, 0x27895020, 0x2789e024, 0x26c95038,
	  0x2849e02c, 0x2789f030, 0x2789e034, 0x288a2024, 0x254a0040,
	  0x288a204c, 0x2849e044, 0x2789f048, 0x2789e04c, 0x25495050,
	  0x27ca3054, 0x28c95058, 0x28ca305c, 0x27c9f060, 0x280a0064,
	  0x26c94078, 0x2849e06c, 0x2789f070, 0x2789e074, 0x288a2064,
	  0x250a0080, 0x288a208c, 0x2849e084, 0x2789f088, 0x2789e08c,
	  0x25094090, 0x27ca3094, 0x28c94098, 0x28ca309c, 0x27c9f0a0,
	  0x280a00a4, 0x2509e0a8, 0x278950ac, 0x2789e0b0, 0x2709e0b4,
	  0x278950b8, 0x2789e0bc, 0x2649e0c0, 0x278950c4, 0x2789e0c8,
	  0x274a40cc, 0x290a50d0, 0x25c970d4, 0x294a30d8, 0x28c970dc,
	  0x28ca30e0, 0x290a40e4, 0x294a50e8, 0x25ca60ec, 0x284a60f0,
	  0x25c970f4, 0x298a30f8, 0x28c970fc, 0x28ca3100, 0x298a6104,
	  0x258a6108, 0x284a610c, 0x25896110, 0x298a3114, 0x28c96118,
	  0x28ca311c, 0x298a6120, 0x29ca4124, 0x290a5128, 0x2a4a912c,
	  0x294a3130, 0x28ca9134, 0x28ca3138, 0x290a413c, 0x294a5140,
	  0x25ca4144, 0x290a5148, 0x2bcaf14c, 0x294a3150, 0x28caf154,
	  0x28ca3158, 0x290a415c, 0x294a5160, 0x284a91f8, 0x258a4168,
	  0x290a516c, 0x2a8aa170, 0x294a3174, 0x28caa178, 0x28ca317c,
	  0x290a4180, 0x294a5184, 0x25ca4188, 0x290a518c, 0x2acab190,
	  0x294a3194, 0x28cab198, 0x28ca319c, 0x290a41a0, 0x294a51a4,
	  0x2b09e1a8, 0x278ac1ac, 0x2789e1b0, 0x2a0aa1e0, 0x2a0ab1ec,
	  0x2849e1bc, 0x278ac1c0, 0x2789e1c4, 0x2589e1c8, 0x278961cc,
	  0x2789e1d0, 0x25c9e1d4, 0x278971d8, 0x2789e1dc, 0x288a2160,
	  0x2b4ad1e4, 0x2a8ad1b4, 0x2b4ad1c4, 0x2b8ae1f0, 0x2acae1b8,
	  0x2b8ae1c4, 0x258961fc, 0x2b0a3200, 0x28c96204, 0x28ca3208,
	  0x25c9720c, 0x2bca3210, 0x28c97214, 0x28ca3218, 0x2a4a921c,
	  0x2a8aa220, 0x2acab224, 0x2b0ac228, 0x258a622c, 0x284a6230,
	  0x25896234, 0x298a3238, 0x28c9623c, 0x28ca3240, 0x298a6244,
	  0x00000001, 0x00000050, 0x00000100, 0x00000200, 0x00000000,
	  0x00000020, 0x00000000, 0x00000008, 0x0000001f, 0x00000050,
	  0x00000002, 0x00000300, 0x00000300, 0x00000000, 0x00000000,
	  0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000021, 0x80000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000 };
  setMemory(mem_temp, 176);
  kuuga(0);
  return (memory[149] == 0x547 && memory[150] == 0x320);

}

bool serial_add_test()
{
  bool zero_flag = false;
  uint32 result1 = bit_serial_add(0x0000000A, 0x00000005, false, &zero_flag);
  uint32 result2 = bit_serial_add(0x0000000F, 0x00000005, true, &zero_flag);
  return (result1 == 0x0000000F && result2 == 0x0000000A);
}
