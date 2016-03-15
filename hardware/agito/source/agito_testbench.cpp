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
bool branch_less_than_register_test();
bool branch_less_than_address_test();
bool branch_equal_register_test();
bool branch_equal_address_test();
bool branch_greater_than_register_test();
bool branch_greater_than_address_test();
bool branch_register_offset_test();
bool branch_address_test();
bool and_register_test();
bool and_constant_test();
bool or_register_test();
bool or_constant_test();
bool not_test();

int main()
{
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Load Direct Test"] = load_direct_test;
  test_funcs["Load Register Offset Test"] = load_register_offset_test;
  test_funcs["Store Direct Test"] = store_direct_test;
  test_funcs["Store Register Offset Test"] = store_register_offset_test;
  test_funcs["Add Constant Test"] = add_constant_test;
  test_funcs["Add Register Test"] = add_register_test;
  test_funcs["Arithmetic Shift Right Test"] = arithmetic_shift_right_test;
  test_funcs["Shift Right Test"] = shift_right_test;
  test_funcs["Arithmetic Shift Left Test"] = arithmetic_shift_left_test;
  test_funcs["Shift Left Test"] = shift_left_test;
  test_funcs["Complement Test"] = complement_test;
  test_funcs["Branch Less Than Register Test"] =
      branch_less_than_register_test;
  test_funcs["Branch Less Than Address Test"] = branch_less_than_address_test;
  test_funcs["Branch Equal Register Test"] =
  	branch_equal_register_test;
  test_funcs["Branch Equal Address Test"] = branch_equal_address_test;
  test_funcs["Branch Greater Than Register Test"] =
  	branch_greater_than_register_test;
  test_funcs["Branch Greater Than Address Test"] =
  	branch_greater_than_address_test;
  test_funcs["Branch Register Offset Test"] = branch_register_offset_test;
  test_funcs["Branch Address Test"] = branch_address_test;
  test_funcs["AND Register Test"] = and_register_test;
  test_funcs["AND Constant Test"] = and_constant_test;
  test_funcs["OR Register Test"] = or_register_test;
  test_funcs["OR Constant Test"] = or_constant_test;
  test_funcs["NOT Test"] = not_test;
  //test_funcs["Multiply Test"] = multiply_test;
  //test_funcs["Divide Test"] = divide_test;
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
  uint32 mem[2] = {0X28100434, 0x00000000};
  uint32 reg_file[5] = {0x0, 0x0, 0x00000022, 0x0, 0x00000044};
  setMemory(mem, 2);
  setRegisters(reg_file, 5);
  agito(0);
  return registers[4] == 0x00000056;
}

bool add_register_test()
{
  uint32 mem[2] = {0X30100403, 0x00000000};
  uint32 reg_file[5] = {0x0, 0x0, 0x00000022, 0x0, 0x00000044};
  setMemory(mem, 2);
  setRegisters(reg_file, 5);
  agito(0);
  return registers[4] == 0x00000022;
}

bool arithmetic_shift_right_test()
{
  uint32 mem[2] = {0X38180007, 0x00000000};
  uint32 reg_file[7] = {0xFFFFF822, 0x0, 0x00000022, 0x0, 0x00000044, 0x0, 0x0};
  setMemory(mem, 2);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[6] == 0xFFFFFFF0;
}

bool shift_right_test()
{
  uint32 mem[2] = {0X4018000A, 0x00000000};
  uint32 reg_file[7] = {0xFFFFF822, 0x0, 0x00000022, 0x0, 0x00000044, 0x0, 0x0};
  setMemory(mem, 2);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[6] == 0x003FFFFE;
}

bool arithmetic_shift_left_test()
{
  uint32 mem[2] = {0X48180807, 0x00000000};
  uint32 reg_file[7] = {0xFFFFF822, 0x0, 0x00000022, 0x0, 0x00000044, 0x0, 0x0};
  setMemory(mem, 2);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[6] == 0x00002200;
}

bool shift_left_test()
{
  uint32 mem[2] = {0X50000007, 0x00000000};
  uint32 reg_file[7] = {0x00000001, 0x0, 0x00000022, 0x0, 0x00000044, 0x0, 0x0};
  setMemory(mem, 2);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[0] == 0x00000080;
}

bool complement_test()
{
  uint32 mem[2] = {0X580C0003, 0x00000000};
  uint32 reg_file[7] = {0x00000001, 0x0, 0x00000022, 0x000170C0,
      0x00000044, 0x0, 0x0};
  setMemory(mem, 2);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[3] == 0xFFFE8F40;
}

bool branch_less_than_register_test()
{
  uint32 mem[4] = {0X60080001, 0x00001010, 0X280C0822, 0x00000000};
  uint32 reg_file[7] = {0x00000001, 0x00000002, 0x00000002, 0x000170C0,
      0x00000044, 0x0, 0x0};
  setMemory(mem, 4);
  setRegisters(reg_file, 7);
  agito(0);
  return registers[3] == 0x66;
}

bool branch_less_than_address_test()
{
  uint32 mem[3] = {0X68100607, 0X28000044, 0x00000000};
  uint32 reg_file[8] = {0x00000001, 0x00000002, 0x00000002, 0x000170C0,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 3);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x45;
}

bool branch_equal_register_test()
{
  uint32 mem[3] = {0X70100405, 0X28000044, 0x00000000};
  uint32 reg_file[8] = {0x00000001, 0x00000002, 0x00000002, 0x000170C0,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 3);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x45;
}

bool branch_equal_address_test()
{
  uint32 mem[8] = {0X78180401, 0X28000044, 0x00000000, 0x00000000,
      0x00000000,0x00000000,0X28000044, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000002, 0x00000002, 0x000170C0,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 8);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x47;
}

bool branch_greater_than_register_test()
{
  uint32 mem[6] = {0X800C0202, 0X28000044, 0x00000000, 0x00000000,
      0X28000024, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000005, 0x00000002, 0x00000004,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 6);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x27;
}

bool branch_greater_than_address_test()
{
  uint32 mem[6] = {0X88C80202, 0X28000044, 0x00000000, 0x00000000,
        0X28000024, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0x00000002, 0x00000004,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 6);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x47;
}

bool branch_register_offset_test()
{
  uint32 mem[7] = {0X90100004, 0X28000044, 0x00000000, 0x00000000,
        0x00000000, 0X28000128, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0x00000002, 0x00000004,
      0x00000001, 0x0, 0x0, 0x00000005};
  setMemory(mem, 7);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x12B;
}

bool branch_address_test()
{
  uint32 mem[9] = {0X98000007, 0X28000044, 0x00000000, 0x00000000,
        0X28000024, 0x00000000, 0x11223344, 0X28000054, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0x00000002, 0x00000004,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 9);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[0] == 0x57;
}

bool and_register_test()
{
  uint32 mem[2] = {0XA0080403, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0xAAAAAAAA, 0x55555555,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 2);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[2] == 0x0;
}

bool and_constant_test()
{
  uint32 mem[2] = {0XA80804FF, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0xAAAAAAAA, 0x55555555,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 2);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[2] == 0xAA;
}

bool or_register_test()
{
  uint32 mem[2] = {0XB0080403, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0xAAAAAAAA, 0x55555555,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 2);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[2] == 0xFFFFFFFF;
}

bool or_constant_test()
{
  uint32 mem[2] = {0XB808041A, 0x00000000};
  uint32 reg_file[8] = {0x00000003, 0x00000001, 0xAAAAAAAA, 0x55555555,
      0x00000044, 0x0, 0x0, 0x00000005};
  setMemory(mem, 2);
  setRegisters(reg_file, 8);
  agito(0);
  return registers[2] == 0xAAAAAABA;
}

bool not_test()
{
  uint32 mem[2] = {0XC0100008, 0x00000000};
  uint32 reg_file[9] = {0x00000003, 0x00000001, 0xAAAAAAAA, 0x55555555,
      0x00000044, 0x0, 0x0, 0x00000005, 0xFFFF0000};
  setMemory(mem, 2);
  setRegisters(reg_file, 9);
  agito(0);
  return registers[4] == 0xFFFF;
}
