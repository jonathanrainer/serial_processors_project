import sys
import re
import argparse
import abc


class InstructionBase(object):
	__metaclass__ = abc.ABCMeta

	@abc.abstractproperty
	def name(self):
		return 
	
	@abc.abstractmethod
	def create_instruction(self, instruction_elements):
		return

class Halt(InstructionBase):

	@property
	def name(self): 
		return "HALT"
	
	def create_instruction(self, instruction_elements):
		return "0x00000000"

class Load(InstructionBase):

	@property
	def name(self):
		return "LOAD"
	
	def create_instruction(self, instruction_elements):	
		register_number = format(int(instruction_elements[0][-1:], base=10), '09b')
		address = format(int(instruction_elements[1][1:], base=16), '018b')	
		return "0x" + hex(int("{0}{1}{2}".format("00001", register_number, address), base=2))[2:].upper() 



class Assembler(object):

	name_map = {sc().name: sc() for sc in InstructionBase.__subclasses__()}

	def parse(self, raw_string):
		instruction_elements = re.split(' ', raw_string)
		return self.name_map[instruction_elements[0]].create_instruction(instruction_elements[1:])	

if __name__=="__main__":
	a  = Assembler()
