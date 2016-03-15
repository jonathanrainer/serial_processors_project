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
        return [["Z", instruction[1], start_location+1], [instruction[2], "Z", start_location+2],
                ["Z", "Z", start_location+3]]

class Gouram(object):

    pseudo_instructions = {c().name: c() for c in KuugaPseudoInstruction.__subclasses__()}

    def expand(self, file_name):
        with open(file_name, 'r') as description_file:
            file_string = description_file.read()
        program = self.split_data_and_code(file_string)
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

    def create_memory_contents(self, program):
        program_counter = 0
        expanded_code = []
        for code_line in program.code:
            expanded_code.extend(self.pseudo_instructions[code_line[0]].expand_instruction(code_line, program_counter))
            program_counter = expanded_code[-1][2]
        # Taking Program Size, Create Memory with enough blanks for Code
        # Replace the placeholders with numbers in the code
        # Pass to some processing method


class Program(object):

    data = None
    code = None

    def __init__(self, data_dict, code_list):
        self.data = data_dict
        self.code = code_list


