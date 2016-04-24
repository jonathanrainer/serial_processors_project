from tools.test_case_generators.raw_file_reader.raw_file_reader import RawFileReader
from tools.assembler.assembler import Assembler
import sys


class Gills(object):
    """
    A class to co-ordinate generating memory contents for given test case files,
    specifically for Agito
    """

    # Create a raw file reader to handle the initial parsing of the test case
    # file.
    raw_file_reader = RawFileReader()
    # Create an assembler to parse each line of code once that stage is reached.
    assembler = Assembler()

    def parse_file(self, file_name):
        """
        Top level function, takes in a file_name and produces the memory
        contents ready to be dumped into the HLS implementations directly.
        :param file_name: The name of the test case file to be operated upon.
        :return: Nothing
        """
        # Create the program object by using the file reader to split code and
        # data.
        program = self.raw_file_reader.split_data_and_code(file_name)
        # Create the memory contents from the program objects
        memory_contents = self.create_memory_contents(program)
        # Print it out in the same format as a C Array so it can be copied
        # directly into HLS.
        print("{ " + ", ".join(memory_contents) + " }")

    def create_memory_contents(self, program):
        """
        Takes in a program object and converts it into a list of hexadecimal
        codes that represent the required memory contents to execute that file.
        :param program: A program object that needs to be converted
        :return: A list of hexadecimal strings to implement the given program
        object.
        """
        # Calculate the point at which the data region of memory starts as the
        # number of elements in of program code + 1
        data_start = len(program.code) + 1
        # Take all the data elements and add on this offset to their location
        # parameter
        program.data = {name: [pair[0]+data_start, pair[1]]
                        for name, pair in program.data.items()}
        # Enumerate over each line of code
        for counter_1, code_line in enumerate(program.code):
            # Enumerate over each element in each line of code
            for counter_2, item in enumerate(code_line):
                # If the element of the line of code is a key in the programs
                # listing of data
                if item in program.data.keys():
                    # Take the memory location that piece of data is at and
                    # insert it as a constant value instead of the name of
                    # the piece of data.
                    program.code[counter_1][counter_2] = \
                        "#" + format(program.data[item][0], 'x')
        # Sort the data values by the location they appear, this accounts for
        # the fact that you can't enumerate a dictionary and always get the
        # same result.
        data_vals = sorted(program.data.values(), key=lambda datum: datum[0])
        # Take each line of programming code and parse it with the assembler
        final_result = [self.assembler.parse(" ".join(x[:-1])).lower()
                        for x in program.code]
        # Add in a HALT instruction
        final_result.extend(["0x00000000"])
        # Extend the results by adding in the data values, formatted correctly
        final_result.extend([format(x[1], '#010x') for x in data_vals])
        # Return the memory contents
        return final_result

if __name__ == "__main__":
    # Create a Gills object
    g = Gills()
    # Parse the file given on the command line.
    g.parse_file(sys.argv[1])
