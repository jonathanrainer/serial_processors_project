import unittest
from assembler import Assembler

class AssemblerUnitTests(unittest.TestCase):

	a = None

	def setUp(self):
		self.a = Assembler()

	def test_parse_halt(self):
		output = self.a.parse("HALT")
		self.assertEqual(output, "0x00000000")

	def test_parse_load(self):
		output = self.a.parse("LOAD R1 #FF2")
		self.assertEqual(output, "0x8040FF2")
		

if __name__ == '__main__':
	unittest.main()
