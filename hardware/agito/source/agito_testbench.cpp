#include "agito.h"
#include <map>
#include <string>

//void setUp();
bool load_direct_test();
bool load_register_offset_test();

int main()
{
  std::map<std::string, bool (*)(void)> test_funcs;
  typedef std::map<std::string, bool (*)(void)>::iterator it_type;
  test_funcs["Load Direct Test"] = load_direct_test;
  test_funcs["Load Register Offset Test"] = load_register_offset_test;
  int passes = 0;
  int fails = 0;
  int tests = 0;
  printf("########## TEST RESULTS ##########\n");
  for(it_type iterator = test_funcs.begin();
      iterator != test_funcs.end(); iterator++)
  {
      tests++;
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

//void setUp()
//{
//  for (int i=0; sizeof(registers)/sizeof(registers[0]); i++)
//  {
//    registers[i] = 0;
//  }
//}

bool load_direct_test()
{
  int mem[4] = {0x080C0002, 0x00000000, 0x22FF22FF, 0xFFEEDDCC};
  agito(mem, 0x0);
  return true;
}

bool load_register_offset_test()
{
  int mem[4] = {0x10140403, 0x00000000, 0x22FF22FF, 0xFFEEDDCC};
  agito(mem, 0x0);
  return true;
}

//
