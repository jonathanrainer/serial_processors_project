import unittest
from assembler import Assembler

class AssemblerUnitTests(unittest.TestCase):

	a = None

	def setUp(self):
		self.a = Assembler()

        def parse_test(self, command, output):
                parsed_text = self.a.parse(command)
                self.assertEqual(parsed_text, output)
        

	def test_parse_halt(self):
		self.parse_test("HALT",  "0X00000000")

	def test_parse_load(self):
		self.parse_test("LOAD R1 #FF2", "0X08040FF2")
	
	def test_parse_load_register_offset(self):
		self.parse_test("LOADRO R1 R2 #27", "0X10040427")

	def test_parse_store(self):
		self.parse_test("STORE #FFFF R7", "0X19FFFE07")

	def test_parse_store_register_offset(self):
		self.parse_test("STORERO R8 #42 R4", "0X20208404")

	def test_parse_add_constant(self):
		self.parse_test("ADDC R7 R2 #77", "0X281C0477")

	def test_parse_add_register(self):
		self.parse_test("ADD R1 R2 R3", "0X30040403")
        
        def test_parse_arithmetic_shift_right(self):
		self.parse_test("ASHR R7 R1 #4", "0X381C0204")

        def test_parse_shift_right(self):
                self.parse_test("SHR R8 R2 #7", "0X40200407")
        
        def test_parse_arithmetic_shift_left(self):
		self.parse_test("ASHL R4 R8 #1", "0X48101001")

        def test_parse_shift_left(self):
                self.parse_test("SHL R2 R5 #3", "0X50080A03")

        def test_parse_complement(self):
                self.parse_test("COMP R2 R4", "0x58080800")

        def test_parse_branch_less_than_register(self):
                self.parse_test("BLTRO R3 R7 R1", "")

        def test_parse_branch_less_than_address(self):
                self.parse_test("BLTA R5 R6 #44", "")

        def test_parse_branch_equal_register(self):
                self.parse_test("BERO R2 R1 R7", "") 

        def test_parse_branch_equal_address(self):
                self.parse_test("BEA R3 R4 #2", "")

        def test_parse_branch_greater_than_register(self):
                self.parse_test("BGTRO R2 R5 R1", "")

        def test_parse_branch_greater_than_address(self):
                self.parse_test("BGTA R3 R2 #7", "")

        def test_parse_branch_register_offset(self):
                self.parse_test("BRO R7 #55", "")

        def test_parse_branch_address(self):
                self.parse_test("BRA #6754", "")

        def test_parse_and_register(self):
                self.parse_test("AND R3 R4 R5", "")

        def test_parse_and_constant(self):
                self.parse_test("ANDC R3 R7 #F", "")

        def test_parse_or_register(self):
                self.parse_test("OR R4 R5 R3", "")

        def test_parse_or_constant(self):
                self.parse_test("OR R4 R7 #1", "")

        def test_parse_not(self):
                self.parse_fail()

        def test_parse_mul(self):
                self.fail()

        def test_parse_div(self):
                self.fail()

        def test_parse_sub(self):
                self.fail()

        

if __name__ == '__main__':
	unittest.main()
