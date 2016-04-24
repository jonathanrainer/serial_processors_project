import re
import argparse
import abc


class AgitoInstructionBase(object):
    """ Abstract class for any Agito Instruction

    Should be used to inherit from so that all implementations of an Agito
    instruction are guaranteed to have methods to create instruction objects
    and also the hexadecimal representation of the instruction the object
    represents.

    """
    __metaclass__ = abc.ABCMeta

    @abc.abstractmethod
    def create_instruction(self, instruction_elements):
        """ Create a hexadecimal code that represents the given instruction
        elements.
        :param instruction_elements: A list of elements that form the
        instruction, will be specific to the kind of instruction that is
        inheriting.
        :return: The hexadecimal code that represents the given instruction
        elements.
        """
        return

    @staticmethod
    def create_hex_representation(element_format_pairs):
        """
        Take in a set of pairs and create the hexadecimal representations
        of each piece of data, corresponding to the format strings.
        :param element_format_pairs: A list of pairs, the first element being
        the piece of data to encode, and the format string that the tells the
        format function how to process the data.
        :return: The concatentation of all the pairs, translated in hexadecimal.
        """
        output = ""  # Create a blank output initialy
        # Iterate over each element, format pair
        for (element, format_string) in element_format_pairs:
            # At each iteration convert the element into hexadecimal and
            # concatenate it to the output.
            output += format(int(element, base=16), format_string)
        # Return the whole output with the heaxdecimal indicator "0X" at the
        # front.
        return format(int(output, base=2), '#010X')


class OneOperandInstruction(AgitoInstructionBase):
    """ Abstract class for a 1 Operand Instruction.

    Provides specificity as to how the instruction should be created from the
    given instruction elements but doesn't specify names or opcodes as they
    will be specified in specific instruction implementations

    Attributes:
        name: A string representing the name of the given instruction
        opcode: A string that reprents the opcode for the instruction in
        hexadecimal.
    """
    __metaclass__ = abc.ABCMeta

    @abc.abstractproperty
    def name(self):
        return

    @abc.abstractproperty
    def opcode(self):
        return

    def create_instruction(self, instruction_elements):
        """
        Takes the set of instruction elements and formats them into a correct
        instruction.

        :param instruction_elements: A set of binary strings to be formed into
        a correct instruction
        :return: The correctly formed, hexadecimal representation of the
        instruction that's represented.
        """
        # In the special case that the opcode is 0, then just pad the
        # instruction elements with 0's because only the opcode is important.
        if self.opcode == "0":
            instruction_elements.extend("0")
        # Create the hexadecimal representation as the 5 bit opcode, followed
        # by the 27bit operand in this case.
        return self.create_hex_representation(
            [(self.opcode, "05b"), (instruction_elements[0], "027b")])


class TwoOperandInstruction(AgitoInstructionBase):
    """ Abstract class for a 2 Operand Instruction.

    Attributes:
        name: A string representing the name of the given instruction
        opcode: A string that reprents the opcode for the instruction in
        hexadecimal.
        short_long_flag: There are two potential implementations of a 2 operand
        instruction, either 18 bits followed by 9 bits (long-short) or
        vice-versa. This flag indicates which form the represented instruction
        is in.
    """
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
        """
        Takes the set of instruction elements and formats them into a correct
        instruction.

        :param instruction_elements: A set of binary strings to be formed into
        a correct instruction
        :return: The correctly formed, hexadecimal representation of the
        instruction that's represented.
        """
        # Set up the format strings for long-short from
        format_strings = ["018b", "09b"]
        # If however the flag is set then reverse the order of the strings.
        if self.short_long_flag:
            format_strings.reverse()
        # Return the hexadecimal representation of the opcode and then the two
        # other instruction elements.
        return self.create_hex_representation(
            [(self.opcode, "05b"), (instruction_elements[0], format_strings[0]),
             (instruction_elements[1], format_strings[1])])


class ThreeOperandInstruction(AgitoInstructionBase):
    """ Abstract class for a 3 Operand Instruction.

    Attributes:
        name: A string representing the name of the given instruction
        opcode: A string that reprents the opcode for the instruction in
        hexadecimal.
    """
    __metaclass__ = abc.ABCMeta

    @abc.abstractproperty
    def name(self):
        return

    @abc.abstractproperty
    def opcode(self):
        return

    def create_instruction(self, instruction_elements):
        # Create a set of pairs that starts with just being the relevant opcode
        pairs = [(self.opcode, "05b")]
        # Extend the list with all the other instruction elements, but adding
        # a format string
        pairs.extend([(x, "09b") for x in instruction_elements])
        # Return the hexadecimal representation
        return self.create_hex_representation(pairs)

# Implementations of all the individual instructions, specifying the names and
# opcodes.


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


class BranchLessThanRegister(ThreeOperandInstruction):
    @property
    def name(self):
        return "BLTR"

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


class BranchEqualRegister(ThreeOperandInstruction):
    @property
    def name(self):
        return "BER"

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


class BranchGreaterThanRegister(ThreeOperandInstruction):
    @property
    def name(self):
        return "BGTR"

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


class BranchRegister(TwoOperandInstruction):
    @property
    def name(self):
        return "BRO"

    @property
    def opcode(self):
        return "12"

    @property
    def short_long_flag(self):
        return True


class BranchAddress(OneOperandInstruction):
    @property
    def name(self):
        return "BA"

    @property
    def opcode(self):
        return "13"

    @property
    def short_long_flag(self):
        return True


class ANDRegister(ThreeOperandInstruction):
    @property
    def name(self):
        return "AND"

    @property
    def opcode(self):
        return "14"


class ANDConstant(ThreeOperandInstruction):
    @property
    def name(self):
        return "ANDC"

    @property
    def opcode(self):
        return "15"


class ORRegister(ThreeOperandInstruction):
    @property
    def name(self):
        return "OR"

    @property
    def opcode(self):
        return "16"


class ORConstant(ThreeOperandInstruction):
    @property
    def name(self):
        return "ORC"

    @property
    def opcode(self):
        return "17"


class NOT(TwoOperandInstruction):
    @property
    def name(self):
        return "NOT"

    @property
    def opcode(self):
        return "18"

    @property
    def short_long_flag(self):
        return True


class Assembler(object):
    """
    Main class for the assembler, co-ordinates the creation of all the
    instructions.
    """
    # Create a list of lists of all the subclasses of the subclasses of
    # AgitoInstructionBase, so all the classes that inherit from the abstract
    # One, Two and Three Operand classes.
    unflattened_list = [y.__subclasses__()
                        for y in AgitoInstructionBase.__subclasses__()]
    # Flatten out the list so there are no more sublists.
    flattened_list = [item for sublist in unflattened_list for item in sublist]
    # Create a dictionary that maps the names of each subclass to an object
    # of that subclass.
    name_map = {sc().name: sc() for sc in flattened_list}

    def parse(self, raw_string):
        """
        Take one line of assembly code and return the hexadecimal code that
        represents that instruction
        :param raw_string: A line of text that is an instruction command
        to the processor.
        :return: The hexadecimal representation of that that assembly
        instruction.
        """
        # Split out the elements of the string wherever there is a space.
        instruction_elements = re.split(' ', raw_string)
        # The first element of each instruction should be it's name,
        # so use that as the key into name_map and then create an instruction
        # from each of the given elements but ignoring their first character.
        return self.name_map[instruction_elements[0]].create_instruction(
            [x[1:] for x in instruction_elements[1:]])


if __name__ == "__main__":
    # Create the argument parser.
    parser = argparse.ArgumentParser(
        description="A tool to process assembly code for Agito processors")
    # Add an argument for the line of assembly code to parse.
    parser.add_argument("line")
    # Create an assembler
    a = Assembler()
    # Print the result of parsing the given line.
    print(a.parse(parser.parse_args().line))
