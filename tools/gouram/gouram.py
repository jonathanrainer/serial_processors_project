import re
import abc


class KuugaPseudoInstruction(object):

    @abc.abstractproperty
    def name(self):
        return

    @abc.abstractmethod
    def expand_instruction(self, instruction, start_location):
        return


class AddPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "ADD"

    def expand_instruction(self, instruction, start_location):
        return [[instruction[1], "Z", start_location+1], ["Z", instruction[2], start_location+2],
                ["Z", "Z", start_location+3]]


class Gouram(object):

    pseudo_instructions = {c().name: c() for c in KuugaPseudoInstruction.__subclasses__()}

    def expand(self, file_name):
        with open(file_name, 'r') as description_file:
            file_string = description_file.read()
        program = self.split_data_and_code(file_string)
        program = self.process_program_object(program)
        return self.create_memory_contents(program)

    @staticmethod
    def split_data_and_code(file_string):
        data_string = re.search("(?<=DATA:\n).*(?=END_DATA\n)", file_string, re.DOTALL).group(0)
        data_list = [re.split(": ", y) for y in [x for x in re.split("\n", data_string) if len(x) > 0]]
        assert([x for x in data_list if len(x) != 2] == [])
        data_dict = {data_pair[0]: [location, int(data_pair[1], base=16)]
                     for location, data_pair in enumerate(data_list)}
        code_string = re.search("(?<=CODE:\n).*(?=END_CODE)", file_string, re.DOTALL).group(0)
        code_list = [re.split(" ", y) for y in [x for x in re.split("\n", code_string) if len(x) > 0]]
        return Program(data_dict, code_list)

    def process_program_object(self, program):
        program_counter = 0
        expanded_code = []
        for code_line in program.code:
            expanded_code.extend(self.pseudo_instructions[code_line[0]].expand_instruction(code_line, program_counter))
            program_counter = expanded_code[-1][2]
        # Add in space for a HALT command
        program_counter += 1
        # Taking Program Size, Create Memory with enough blanks for Code
        program.data = {name: [pair[0]+program_counter, pair[1]] for name, pair in program.data.items()}
        program.code = expanded_code
        return program

    def create_memory_contents(self, program):
        result = [self.codeline_to_hexadecimal(x, program.data) for x in program.code]
        result.extend(["0x00000001"])
        data_vals = sorted(program.data.values(), key=lambda datum: datum[0])
        result.extend([format(x[1], "#010x") for x in data_vals])
        return "{ \"" + "\", \"".join(result) + "\" }"

    @staticmethod
    def codeline_to_hexadecimal(codeline, data):
        first_op = data[codeline[0]][0]
        second_op = data[codeline[1]][0]
        third_op = codeline[2]
        binary_string = "{0}{1}{2}00".format(format(first_op, "010b"), format(second_op, "010b"),
                                             format(third_op, "010b"))
        return format(int(binary_string, base=2), "#010x")


class Program(object):

    data = {}
    code = []

    def __init__(self, data_dict, code_list):
        self.data = data_dict
        self.code = code_list
