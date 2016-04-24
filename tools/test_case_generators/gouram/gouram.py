from tools.test_case_generators.raw_file_reader.raw_file_reader \
    import RawFileReader
import abc
import sys


class KuugaPseudoInstruction(object):
    """
    An abstract class that represents a Pseudo-Assembly language instruction.
    Crucially it contains a method that allows the instruction to be expanded.
    Either into a set of Pseduo-Instructions that themselves have to be
    expanded, or into a set of SUBLEQ instructions.

    Attributes:
        name: The name of the PseudoInstruction
    """

    @abc.abstractproperty
    def name(self):
        return

    @abc.abstractmethod
    def expand_instruction(self, instruction, start_location):
        """
        An abstract method that creates, from a given instruction, the expansion
        of the instruction into either more instructions that need expanding
        or a set of SUBLEQ instructions. Or some combination of the two
        :param instruction: A list of strings that represent a high level
        instruction.
        :param start_location: The place the instruction occurs in memory,
        so that jumps can be made relative to it.
        :return: A list of sublists that contain either the operands needed
        for SUBLEQ or the instructions to be further expanded.
        """
        return


class AddPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that adds the contents of two memory
    locations together, storing the result in the first given location.
    Descriptions of inherited fields are given in the abstract class.

    """

    @property
    def name(self):
        return "ADD"

    def expand_instruction(self, instruction, start_location):
        return [
            # Subtract the first operand from 0, stored in TADD,
            # a temporary variable.
            [instruction[2], "TADD", start_location+1],
            # Subtract the next instruction from TADD
            ["TADD", instruction[1], start_location+2],
            # Zero TADD so it can be used again
            ["TADD", "TADD", start_location+3]
        ]


class SubtractPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that subtracts the contents of
    two memory locations, storing the result in the first given
    location. Descriptions of inherited fields are given in the abstract class.

    """

    @property
    def name(self):
        return "SUB"

    def expand_instruction(self, instruction, start_location):
        # Simply call SUBLEQ with the instructions in the correct order.
        return [[instruction[2], instruction[1], start_location+1]]


class NOTPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that calculates the bitwise NOT of
    the contents of a given memory location and stores the result in that
    memory location.  Descriptions of inherited fields are given in the
    abstract class.

    """

    @property
    def name(self):
        return "NOT"

    def expand_instruction(self, instruction, start_location):
        return [
            # Subtract the given operand from TNOT (a temporary variable
            # set to 0)
            ["SUB", "TNOT", instruction[1], start_location+1],
            # Subtract 1 from TNOT
            ["SUB", "TNOT", "ON", start_location+2],
            # Move the result from TNOT to the original location
            ["MOVE", instruction[1], "TNOT", start_location+3],
            # Zero TNOT so it can be used again
            ["TNOT", "TNOT", start_location+4]]


class MultiplyPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that multiplies the contents of two
    memory locations together stores the result in the first memory location.
    Descriptions of inherited fields are given in the abstract class.

    """

    @property
    def name(self):
        return "MUL"

    def expand_instruction(self, instruction, start_location):
        return [
            # Copy the second operand into a temporary variable TMUL1
            ["COPY", "TMUL1", instruction[2], start_location+1],
            # Subtract 1 from TMUL1 to check if the loop can break or more
            # needs to be added.
            ["ON", "TMUL1", start_location+4],
            # Add the first operand to TMUL2 where the multiplication
            # accumulates
            ["ADD", "TMUL2", instruction[1], start_location+3],
            # Jump back to the loop test.
            ["Z", "Z", start_location+1],
            # Add one last amount because the branch occurs at 0 which is not
            # desirable but unavoidable
            ["ADD", instruction[1], "TMUL2",  start_location+5],
            # Zero both the temporary locations.
            ["TMUL1", "TMUL1", start_location+6],
            ["TMUL2", "TMUL2", start_location+7]
        ]


class MOVEPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that moves the contents of one
    memory location to another, it zeroes the original memory location.
    Descriptions of inherited fields are given in the abstract class.

    """

    @property
    def name(self):
        return "MOVE"

    def expand_instruction(self, instruction, start_location):
        return [
            # Zero the location that is being moved into
            [instruction[1], instruction[1], start_location+1],
            # Set TMOVE to the negative of the second operand
            [instruction[2], "TMOVE", start_location+2],
            # Set the contents of the first memory location to minus TMOVE
            # (so the original contents of instruction[2]).
            ["TMOVE", instruction[1], start_location + 3],
            # Zero TMOVE and move on.
            ["TMOVE", "TMOVE", start_location + 4]
        ]


class DividePseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that divides the contents of the
    first memory location by the second, storing the result in the first
    memory location. Descriptions of inherited fields are given in the abstract
    class.

    """

    @property
    def name(self):
        return "DIV"

    def expand_instruction(self, instruction, start_location):
        return [
            # Subtract the second operand from the first, if this produces a
            # positive result then there is more dividing to do, otherwise
            # break to the zero test.
            [instruction[2], instruction[1], start_location+3],
            # Add 1 to TDIV1, a Temporary Variable, the accumulating result
            ["ADD", "TDIV1", "ON", start_location+2],
            # Branch back to the break check.
            ["Z", "Z", start_location],
            # Because the break test above branches on 0 or less then there's
            # the possibility that the last subtraction actually produced a
            # negative result (i.e there's not enough to divide properly and
            # what's left is the remainder). So subtract 0 from the first
            # operand (the one that's been decreasing). If that produces a 0
            # result then one needs to be added, otherwise do nothing.
            [instruction[1], "TDIV2", start_location+5],
            # Move into the final clean up phase.
            ["Z", "Z", start_location+6],
            # Add 1 to TDIV 1 to account for this extra subtraction found above.
            ["ADD", "TDIV1", "ON", start_location+4],
            # Move the result from the temporary variable into the first memory
            # operand.
            ["MOVE", instruction[1], "TDIV1", start_location+7],
            # Zero both the temporary variables.
            ["TDIV1", "TDIV1", start_location+8],
            ["TDIV2", "TDIV2", start_location+9]
        ]


class ShiftLeftPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that left shifts the contents of the
    first memory location by the number of bits specified in the second
    location, storing the result in the first memory location. Descriptions of
    inherited fields are given in the abstract class.

    """

    @property
    def name(self):
        return "SHL"

    def expand_instruction(self, instruction, start_location):
        return [
            # Copy the amount to shift into TSHIFT, a temporary variable
            ["COPY", "TSHIFT", instruction[2], start_location+1],
            # Add 1 to the amount to shift because of the branching occurring at
            # 0.
            ["ADD", "TSHIFT", "ON", start_location+2],
            # Subtract 1 from TSHIFT, if this produces a negative result then
            # keep multiplying by 2. Otherwise break.
            ["ON", "TSHIFT", start_location+5],
            # Doubling and multiplying by 2 are synonymous so double
            # the contents of the first memory location.
            ["ADD", instruction[1], instruction[1], start_location+4],
            # Unconditionally branch to the break test.
            ["Z", "Z", start_location+2]
        ]


class ShiftRightPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that right shifts the contents of
    the first memory location by the number of bits specified in the second
    location, storing the result in the first memory location. Descriptions of
    inherited fields are given in the abstract class.

    """


    @property
    def name(self):
        return "SHR"

    def expand_instruction(self, instruction, start_location):
        return [
            # Copy the amount to shift into TSHIFT, a temporary variable
            ["COPY", "TSHIFT", instruction[2], start_location+1],
            # Add 1 to the amount to shift because of the branching occurring at
            # 0.
            ["ADD", "TSHIFT", "ON", start_location+2],
            # Subtract 1 from TSHIFT, if this produces a negative result then
            # keep multiplying by 2. Otherwise break.
            ["ON", "TSHIFT", start_location+5],
            # Divide the contents of the first memory location by SHC1, a
            # constant that is set to the value 2.
            ["DIV", instruction[1], "SHC1", start_location+4],
            # Unconditionally branch to the break test.
            ["Z", "Z", start_location+2]
        ]


class COPYPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that copies the contents of
    one memory location to another. Descriptions of inherited fields are given
    in the abstract class.

    """

    @property
    def name(self):
        return "COPY"

    def expand_instruction(self, instruction, start_location):
        return [
            # Subtract the contents of the second memory location from TCOPY1,
            # a temporary variable set to 0.
            [instruction[2], "TCOPY1", start_location+1],
            # Subtract TCOPY1 from TCOPY2 so TCOPY2 contains the original value
            # stored in the second memory location.
            ["TCOPY1", "TCOPY2", start_location+2],
            # Move the value stored in TCOPY2 to the location of the first
            # operand.
            ["MOVE", instruction[1], "TCOPY2", start_location+3],
            # Zero both the temporary variables.
            ["TCOPY1", "TCOPY1", start_location+4],
            ["TCOPY2", "TCOPY2", start_location+5]
        ]


class ANDPseudoInstruction(KuugaPseudoInstruction):
    """
    A concrete implementation of a function that calculates the bitwise AND
    of the contents of two memory locations. Descriptions of inherited fields
    are given in the abstract class.

    """

    @property
    def name(self):
        return "AND"

    def expand_instruction(self, instruction, start_location):
        return [
            # Copy the AND Contants and the second operand to temporary
            # locations.
            ["COPY", "TAND1", "ANDC1", start_location+1],
            ["COPY", "TAND7", instruction[2], start_location+2],
            # Main
            # Subtract 1 from TAND1, if zero is reached then branch
            ["ON", "TAND1", start_location+18],
            # Copy the two operands into temporary variables
            ["COPY", "TAND2", instruction[1], start_location+4],
            ["COPY", "TAND3", instruction[2], start_location+5],
            # Shift the result left by 1 bit so the new bit is exposed
            ["ADD", "TAND4", "TAND4", start_location+6],
            # Subtract the 2nd AND constant from the operands, if
            # a negative or zero result is produced then jump to the zero-test
            # in either case.
            ["ANDC2", "TAND2", start_location+12],
            ["ANDC2", "TAND3", start_location+15],
            # Operation
            # Set the new bit to the value 1 by adding 1
            ["ADD", "TAND4", "ON", start_location+9],
            # Shift the two operands left by 1
            ["ADD", instruction[1], instruction[1], start_location+10],
            ["ADD", instruction[2], instruction[2], start_location+11],
            # Unconditonally jump to the break test.
            ["Z", "Z", start_location+2],
            # Zero Check
            # Zero the value in TAND5
            ["TAND5", "TAND5", start_location+13],
            # Subtract TAND2 from TAND5, if a 0 results then the bit was present
            # originally so go and check the second operand
            ["TAND2", "TAND5", start_location+7],
            # If the result is positive then the original subtraction produced
            # a negative result so move onto shifting up both operands.
            ["TAND5", "TAND5", start_location+9],
            # Zero Check2
            # Zero the value in TAND6
            ["TAND6", "TAND6", start_location+16],
            # Subtract TAND3 from TAND6, if a 0 results then the bit was present
            # originally so go and check the second operand
            ["TAND3", "TAND6", start_location+8],
            # If the result is positive then the original subtraction produced
            # a negative result so move onto shifting up both operands.
            ["TAND6", "TAND6", start_location+9],
            # Cleanup
            # Move TAND4 and TAND7 to the original memory locations so the
            # second operand is retained.
            ["MOVE", instruction[1], "TAND4", start_location+19],
            ["MOVE", instruction[2], "TAND7", start_location+20],
            # Clean up the temporary locations.
            ["TAND1", "TAND1", start_location+21],
            ["TAND2", "TAND2", start_location+22],
            ["TAND3", "TAND3", start_location+23],
            ["TAND4", "TAND4", start_location+24]
        ]


class Gouram(object):
    """
    The main class, co-ordinates the unpacking of the test-case files into
    executable assembly code for Kuuga.
    """

    # Create a dictionary that maps the name of classes to objects of those
    # classes.
    pseudo_instructions = {c().name: c()
                           for c in KuugaPseudoInstruction.__subclasses__()}
    # Create a raw file reader to make reading in the test case files easier.
    raw_file_reader = RawFileReader()

    def expand(self, file_name):
        """
        The main method in the class, takes a file in and produces a set of
        memory contents that can be executed on Kuuga correctly.
        :param file_name: A string that represents the name of the test case to
        be converted.
        :return: A string that represents the memory contents.
        """
        # Create a program file to store the data and code from the test case
        # files.
        program = self.raw_file_reader.split_data_and_code(file_name)
        # Process the program object to calculate the data locations and
        # expand the programs given.
        program = self.process_program_object(program)
        # Create the memory contents from the expanded program object.
        return self.create_memory_contents(program)

    def process_program_object(self, program):
        """
        Take in the program object and expand the code, then account for the
        placement of data and make sure all the addresses are correct.
        :param program: A program object, extracted from the test-case file, to
        be expanded
        :return: A program object with all expansions completed.
        """
        # Expand the program code
        expanded_code = self.expand_code(program.code)
        # Calculate the value of the program_counter to start with
        program_counter = len(expanded_code)
        # Add in space for a HALT command
        program_counter += 1
        # Taking Program Size, Create Memory with enough blanks for Code
        program.data = {name: [pair[0]+program_counter, pair[1]]
                        for name, pair in program.data.items()}
        # Store the expanded code in the program object.
        program.code = expanded_code
        return program

    def create_memory_contents(self, program):
        """
        Taking the expanded program object create the memory contents that
        expanded program entails.
        :param program: A program object that contains all sections expanded
        and names replaced with memory locations.
        :return: The string that represents the memory contents.
        """
        # Convert each codeline to hexadecimal and then extend with a HALT
        # command.
        result = [self.codeline_to_hexadecimal(x, program.data)
                  for x in program.code]
        result.extend(["0x00000001"])
        # Create a list of data values because you can't reliably extract
        # them from a dictionary in the correct order.
        data_vals = sorted(program.data.values(), key=lambda datum: datum[0])
        # Extend the program code with all the data values, formatted correctly.
        result.extend([format(x[1], "#010x") for x in data_vals])
        # Add brackets and commas so the result is a valid C Array.
        return "{ " + ", ".join(result) + " }"

    @staticmethod
    def codeline_to_hexadecimal(codeline, data):
        """
        Take in a codeline, and all the data and extract a correct length string
        that represents the codeline but in hexadecimal code.
        :param codeline: A triple that represents the three arguments to SUBLEQ
        :param data: The data from the program object so that locations can
        be extracted
        :return: A formatted string that represents the codeline as a
        hexadecimal string.
        """
        # Extract each of the three locations in turn, the first two as data
        # items and the third as an address
        first_op = data[codeline[0]][0]
        second_op = data[codeline[1]][0]
        third_op = codeline[2]
        # Create a binary string from the operands
        binary_string = "{0}{1}{2}00".format(
            format(first_op, "010b"), format(second_op, "010b"),
            format(third_op, "010b"))
        # Take the binary string and return it as a 32-bit hexadecimal string.
        return format(int(binary_string, base=2), "#010x")

    def expand_code(self, code):
        """
        Take the code object, a list of the instructions to the processor,
        and expand them so eventually the whole function is encoded in SUBLEQ.
        :param code: A list of codelines, a codeline being a list of 4 elements
        where the first element is either the name of a pseudo instruction or is
        an argument to SUBLEQ, the next two elements are arguments and then the
        last element is a line number.
        :return: The list of expanded triples where each triple is the three
        arguments needed by SUBLEQ.
        """
        # Set the result to be the original code list
        expanded_code = code
        # Until there are no more instructions to expand
        while True:
            # Assume that there are no more instructions to expand
            end_of_loop = True
            # Iterate over the expanded code
            for counter, code_line in enumerate(expanded_code):
                # If the first element of the code line is one of the defined
                # pseduo instructions then expand, otherwise just move on
                if code_line[0] in self.pseudo_instructions.keys():
                    # If an instruction is expanded and takes up more space
                    # then all the destinations need to be altered by the
                    # amount the list has grown by. So work out which
                    # instructions will need to be altered.
                    destinations_to_alter = [
                        destination
                        for destination, x in enumerate(expanded_code)
                        if x[-1] > counter and destination != counter]
                    # Perform the expansion
                    expansion = self.pseudo_instructions[code_line[0]].\
                        expand_instruction(code_line, counter)
                    # Iterate over the destinations that need to be altered
                    # and add the offset.
                    for destination in destinations_to_alter:
                        expanded_code[destination][-1] += (len(expansion) - 1)
                    # Insert the expanded code as a replacement for the
                    # instruction that was expanded.
                    expanded_code = expanded_code[:counter] + expansion + \
                                    expanded_code[counter+1:]
                    # Now an expansion has happened it cannot be the case that
                    # all the instructions were expanded.
                    end_of_loop = False
                    # Break out of the inner loop
                    break
            # If no expansions have happened over the course of the whole loop
            # then break.
            if end_of_loop:
                break
        # Return the expanded code.
        return expanded_code


if __name__ == "__main__":
    # Create a Gouram object
    g = Gouram()
    # Print the result of expanding the test case file given on the command
    # line.
    print(g.expand(sys.argv[1]))
