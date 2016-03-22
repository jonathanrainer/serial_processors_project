from tools.test_case_generators.raw_file_reader.raw_file_reader import RawFileReader
from tools.assembler.assembler import Assembler
import sys

class Gills(object):

    raw_file_reader = RawFileReader()
    assembler = Assembler()

    def parse_file(self, file_name):
        program = self.raw_file_reader.split_data_and_code(file_name)
        memory_contents = self.create_memory_contents(program)
        print("{ " + ", ".join(memory_contents) + " }")

    def create_memory_contents(self, program):
        data_start = len(program.code)
        program.data = {name: [pair[0]+data_start, pair[1]] for name, pair in program.data.items()}
        for counter_1, code_line in enumerate(program.code):
            for counter_2, item in enumerate(code_line):
                if item in program.data.keys():
                    program.code[counter_1][counter_2] = "#" + str(program.data[item][0])
        final_result = [self.assembler.parse(" ".join(x[:-1])).lower() for x in program.code]
        final_result.extend([format(x[1], '#010x') for x in program.data.values()])
        return final_result

if __name__ == "__main__":
    g = Gills()
    g.parse_file(sys.argv[1])
