import unittest
from assembler import Assembler

class AssemblerUnitTests(unittest.TestCase):

	a = None

	def setUp(self):
		self.a = Assembler()

	def test_parse_halt(self):
		output = self.a.parse("HALT")
		self.assertEqual(output, "0X00000000")

	def test_parse_load(self):
		output = self.a.parse("LOAD R1 #FF2")
		self.assertEqual(output, "0X08040FF2")
	
	def test_parse_load_register_offset(self):
		output = self.a.parse("LOADRO R1 R2 #27")
		self.assertEqual(output, "0X10040427")

	def test_parse_store(self):
		output = self.a.parse("STORE #FFFF R7")
		self.assertEqual(output, "0X19FFFE07")

	def test_parse_store_register_offset(self):
		output = self.a.parse("STORERO R8 #42 R4")
		self.assertEqual(output, "0X20208404")		

if __name__ == '__main__':
	unittest.main()
