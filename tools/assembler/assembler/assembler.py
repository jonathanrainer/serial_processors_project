import sys
import re
import argparse
import abc


class InstructionBase(object):
	__metaclass__ = abc.ABCMeta
	
	@abc.abstractmethod
	def create_instruction(self, instruction_elements):
		return

	def create_hex_representation(self, element_format_pairs):
		output = ""
		for (element, format_string) in element_format_pairs:
			output += format(int(element, base=16), format_string)
		return format(int(output, base=2), '#010X') 

class OneOperandInstruction(InstructionBase):
	__metaclass__ = abc.ABCMeta

	@abc.abstractproperty
	def name(self):
		return 

	@abc.abstractproperty
	def opcode(self):
		return	

	def create_instruction(self, instruction_elements):
		return self.create_hex_representation([(self.opcode,"05b"),("0", "027b")])

class Halt(OneOperandInstruction):

	@property
	def name(self): 
		return "HALT"
	
	@property
	def opcode(self):
		return "0"

class Load(InstructionBase):

	@property
	def name(self):
		return "LOAD"
	
	@property
	def opcode(self):
		return "1"

	def create_instruction(self, instruction_elements):	
		return self.create_hex_representation(
			[(self.opcode,"05b"), (instruction_elements[0], "09b"), (instruction_elements[1], "018b")])



class LoadRegisterOffset(InstructionBase):

	@property
	def name(self):
		return "LOADRO"

	@property
	def opcode(self):
		return "2"
	
	def create_instruction(self, instruction_elements):
		pairs = [(self.opcode, "05b")]
		pairs.extend([(x, "09b") for x in instruction_elements])
		return self.create_hex_representation(pairs)  

class Store(InstructionBase):

	@property
	def name(self):
		return "STORE"
	
	@property
	def opcode(self):
		return "3"

	def create_instruction(self, instruction_elements):	
		return self.create_hex_representation(
			[(self.opcode,"05b"), (instruction_elements[0], "018b"), (instruction_elements[1], "09b")])



class StoreRegisterOffset(InstructionBase):

	@property
	def name(self):
		return "STORERO"

	@property
	def opcode(self):
		return "4"
	
	def create_instruction(self, instruction_elements):
		pairs = [(self.opcode, "05b")]
		pairs.extend([(x, "09b") for x in instruction_elements])
		return self.create_hex_representation(pairs)  
	
	
class Assembler(object):
	
	unflattened_list = [y.__subclasses__() for y in InstructionBase.__subclasses__()]
	flattened_list = [item for sublist in unflattened_list for item in sublist]

	name_map = {sc().name: sc() for sc in flattened_list}

	def parse(self, raw_string):
		instruction_elements = re.split(' ', raw_string)
		return self.name_map[instruction_elements[0]].create_instruction(
				[x[1:] for x in instruction_elements[1:]])	

if __name__=="__main__":
	a  = Assembler()
