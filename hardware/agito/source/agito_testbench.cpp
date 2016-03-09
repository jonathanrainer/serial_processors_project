#include "agito.h"
#include <map>
#include <string>

void setUp();
void setMemory(uint32 * new_mem, int size);
bool load_direct_test();
bool load_register_offset_test();
bool store_direct_test();
bool store_register_offset_test();
bool add_register_test();
bool add_constant_test();
bool arithmetic_shift_right_test();
bool shift_right_test();
bool arithmetic_shift_left_test();
bool shift_left_test();
bool complement_test();

int main()
{
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Load Direct Test"] = load_direct_test;
  test_funcs["Load Register Offset Test"] = load_register_offset_test;
  test_funcs["Store Direct Test"] = store_direct_test;
  test_funcs["Store Register Offset Test"] = store_register_offset_test;
  test_funcs["Add Register Test"] = add_register_test;
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
  for(int i = 0; i < REG_NUM; i++)
    {
      registers[i] = 0;
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

void setRegisters(uint32 * new_reg_file, int size)
{
  assert(size <= REG_NUM);
  for(int i = 0; i < size; i++)
    {
      registers[i] = new_reg_file[i];
    }
  return;
}

bool load_direct_test()
{
  uint32 mem[3] = {0x08040002, 0x00000000, 0x22FF22FF};
  setMemory(mem, 3);
  agito(0);
  return registers[1] == 0x22FF22FF;
}

bool load_register_offset_test()
{
  uint32 mem[5] = {0x10080601, 0x00000000, 0x00000003, 0x22222222, 0xFFEEDDCC};
  uint32 reg_file[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000003};
  setMemory(mem, 5);
  setRegisters(reg_file, 4);
  agito(0);
  return registers[2] == 0xFFEEDDCC;
}

bool store_direct_test()
{
  uint32 mem[5] = {0X18000800, 0x00000000, 0x00000003, 0x22222222, 0xFFEEDDCC};
  uint32 reg_file[1] = {0xFFAA5522};
  setMemory(mem, 5);
  setRegisters(reg_file, 1);
  agito(0);
  return memory[4] == 0xFFAA5522;
}

bool store_register_offset_test()
{
  uint32 mem[3] = {0X20100406, 0x00000000, 0x00000000};
  uint32 reg_file[7] = {0xFFAA5522, 0x0, 0x0, 0x0, 0x0, 0x0, 0x44444444};
  setMemory(mem, 3);
  setRegisters(reg_file, 7);
  agito(0);
  return memory[2] == 0x44444444;
}

bool add_constant_test()
{
  uint32 mem[2] = {0X30100403, 0x00000000};
  uint32 reg_file[5] = {0x0, 0x0, 0x00000022, 0x0, 0x00000044};
  setMemory(mem, 2);
  setRegisters(reg_file, 5);
  agito(0);
  return registers[3] == 0x00000066;
}

bool add_register_test()
{
  uint32 mem[2] = {0X30100403, 0x00000000};
  uint32 reg_file[5] = {0x0, 0x0, 0x00000022, 0x0, 0x00000044};
  setMemory(mem, 2);
  setRegisters(reg_file, 5);
  agito(0);
  return registers[3] == 0x00000066;
}

bool add_constant_test()
{
  return false;
}

bool arithmetic_shift_right_test()
{
  return false;
}

bool shift_right_test()
{
  return false;
}
