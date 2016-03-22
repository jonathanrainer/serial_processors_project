from tools.test_case_generators.raw_file_reader.raw_file_reader import RawFileReader
from tools.assembler.assembler import Assembler


class Gills(object):

    raw_file_reader = RawFileReader()
    assembler = Assembler()

    def parse_file(self, file_name):
        program = self.raw_file_reader.split_data_and_code(file_name)
        memory_contents = self.create_memory_contents(program)
        print("{ " + ", ".join(memory_contents) + " }")

    def create_memory_contents(self, program):
        return 1

if __name__ == "__main__":
    g = Gills()
