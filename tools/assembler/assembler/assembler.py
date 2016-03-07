import sys
import re
import argparse
import abc


class AgitoInstructionBase(object):
	__metaclass__ = abc.ABCMeta
	
	@abc.abstractmethod
	def create_instruction(self, instruction_elements):
		return

	def create_hex_representation(self, element_format_pairs):
		output = ""
		for (element, format_string) in element_format_pairs:
			output += format(int(element, base=16), format_string)
		return format(int(output, base=2), '#010X') 

class OneOperandInstruction(AgitoInstructionBase):
	__metaclass__ = abc.ABCMeta

	@abc.abstractproperty
	def name(self):
		return 

	@abc.abstractproperty
	def opcode(self):
		return	

	def create_instruction(self, instruction_elements):
		return self.create_hex_representation([(self.opcode,"05b"),("0", "027b")])

class TwoOperandInstruction(AgitoInstructionBase):
	__metaclass__ = abc.ABCMeta

	@abc.abstractproperty
	def name(self):
		return 

	@abc.abstractproperty
	def opcode(self):
		return	

	@abc.abstractproperty
	def short_long_flag(self):
		return

	def create_instruction(self, instruction_elements):
		format_strings = ["018b", "09b"]
		if self.short_long_flag:
			format_strings.reverse()
		return self.create_hex_representation(
			[(self.opcode,"05b"), (instruction_elements[0], format_strings[0]),
						 (instruction_elements[1], format_strings[1])]) 

class ThreeOperandInstruction(AgitoInstructionBase):
	__metaclass__ = abc.ABCMeta

	@abc.abstractproperty
	def name(self):
		return 

	@abc.abstractproperty
	def opcode(self):
		return	
	
	def create_instruction(self, instruction_elements):
		pairs = [(self.opcode, "05b")]
		pairs.extend([(x, "09b") for x in instruction_elements])
		return self.create_hex_representation(pairs)  

class Halt(OneOperandInstruction):

	@property
	def name(self): 
		return "HALT"
	
	@property
	def opcode(self):
		return "0"

class Load(TwoOperandInstruction):

	@property
	def name(self):
		return "LOAD"
	
	@property
	def opcode(self):
		return "1"

	@property
	def short_long_flag(self):
		return True


class LoadRegisterOffset(ThreeOperandInstruction):

	@property
	def name(self):
		return "LOADRO"

	@property
	def opcode(self):
		return "2"  

class Store(TwoOperandInstruction):

	@property
	def name(self):
		return "STORE"
	
	@property
	def opcode(self):
		return "3"

	@property
	def short_long_flag(self):
		return False

class StoreRegisterOffset(ThreeOperandInstruction):

	@property
	def name(self):
		return "STORERO"

	@property
	def opcode(self):
		return "4"

class AddConstant(ThreeOperandInstruction):

        @property
        def name(self):
                return "ADDC"

        @property
        def opcode(self):
                return "5"

class AddRegister(ThreeOperandInstruction):

        @property
        def name(self):
                return "ADD"

        @property
        def opcode(self):
                return "6"

class ArithmeticShiftRight(ThreeOperandInstruction):

        @property
        def name(self):
                return "ASHR"

        @property
        def opcode(self):
                return "7"

class ShiftRight(ThreeOperandInstruction):

        @property
        def name(self):
                return "SHR"

        @property
        def opcode(self):
                return "8"

class ArithmeticShiftLeft(ThreeOperandInstruction):

        @property
        def name(self):
                return "ASHL"

        @property
        def opcode(self):
                return "9"


class ShiftLeft(ThreeOperandInstruction):

        @property
        def name(self):
                return "SHL"

        @property
        def opcode(self):
                return "A"

class Complement(TwoOperandInstruction):

        @property
        def name(self):
                return "COMP"

        @property
        def opcode(self):
                return "B"

        @property
        def short_long_flag(self):
                return True

class BranchLessThanRegisterOffset(ThreeOperandInstruction):

        @property
        def name(self):
                return "BLTRO"

        @property
        def opcode(self):
                return "C"

class BranchLessThanAddress(ThreeOperandInstruction):

        @property
        def name(self):
                return "BLTA"

        @property
        def opcode(self):
                return "D"


class BranchEqualRegisterOffset(ThreeOperandInstruction):

        @property
        def name(self):
                return "BERO"

        @property
        def opcode(self):
                return "E"

class BranchEqualAddress(ThreeOperandInstruction):

        @property
        def name(self):
                return "BEA"

        @property
        def opcode(self):
                return "F"

class BranchGreaterThanRegisterOffset(ThreeOperandInstruction):

        @property
        def name(self):
                return "BGTRO"

        @property
        def opcode(self):
                return "10"

class BranchGreaterThanAddress(ThreeOperandInstruction):

        @property
        def name(self):
                return "BGTA"

        @property
        def opcode(self):
                return "11"

class BranchRegisterOffset(TwoOperandInstruction):

        @property
        def name(self):
                return "BRO"

        @property
        def opcode(self):
                return "12"

        @property
        def short_long_flag(self):
                return True

class BranchAddress(TwoOperandInstruction):

        @property
        def name(self):
                return "BA"

        @property
        def opcode(self):
                return "13"

        def short_long_flag(self):
                return True

class Assembler(object):
	
	unflattened_list = [y.__subclasses__() for y in AgitoInstructionBase.__subclasses__()]
	flattened_list = [item for sublist in unflattened_list for item in sublist]

	name_map = {sc().name: sc() for sc in flattened_list}

	def parse(self, raw_string):
		instruction_elements = re.split(' ', raw_string)
		return self.name_map[instruction_elements[0]].create_instruction(
				[x[1:] for x in instruction_elements[1:]])	

if __name__=="__main__":
	a  = Assembler()
