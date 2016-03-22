from tools.test_case_generators.raw_file_reader.raw_file_reader import RawFileReader
import abc
import sys


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
        return [[instruction[2], "TADD", start_location+1], ["TADD", instruction[1], start_location+2],
                ["TADD", "TADD", start_location+3]]


class SubtractPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "SUB"

    def expand_instruction(self, instruction, start_location):
        return [[instruction[2], instruction[1], start_location+1]]


class NOTPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "NOT"

    def expand_instruction(self, instruction, start_location):
        return [["SUB", "TNOT", instruction[1], start_location+1], ["SUB", "TNOT", "ON", start_location+2],
                ["MOVE", instruction[1], "TNOT", start_location+3], ["TNOT", "TNOT", start_location+4]]


class MultiplyPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "MUL"

    def expand_instruction(self, instruction, start_location):
        return [["COPY", "TMUL1", instruction[2], start_location+1],
                ["ON", "TMUL1", start_location+4], ["ADD", "TMUL2", instruction[1], start_location+3],
                ["Z", "Z", start_location+1], ["ADD", instruction[1], "TMUL2",  start_location+5],
                ["TMUL1", "TMUL1", start_location+6], ["TMUL2", "TMUL2", start_location+7]]


class MOVEPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "MOVE"

    def expand_instruction(self, instruction, start_location):
        return [[instruction[1], instruction[1], start_location+1], [instruction[2], "TMOVE", start_location+2],
                ["TMOVE", instruction[1], start_location + 3], ["TMOVE", "TMOVE", start_location + 4]]


class DividePseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "DIV"

    def expand_instruction(self, instruction, start_location):
        return [[instruction[2], instruction[1], start_location+3],
                ["ADD", "TDIV1", "ON", start_location+2], ["Z", "Z", start_location],
                [instruction[1], "TDIV2", start_location+5], ["Z", "Z", start_location+6],
                ["ADD", "TDIV1", "ON", start_location+4],
                ["MOVE", instruction[1], "TDIV1", start_location+7], ["TDIV1", "TDIV1", start_location+8],
                ["TDIV2", "TDIV2", start_location+9]]


class ShiftLeftPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "SHL"

    def expand_instruction(self, instruction, start_location):
        return [["COPY", "TSHIFT", instruction[2], start_location+1],
                ["ADD", "TSHIFT", "ON", start_location+2], ["ON", "TSHIFT", start_location+5],
                ["ADD", instruction[1], instruction[1], start_location+4], ["Z", "Z", start_location+2]]


class ShiftRightPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "SHR"

    def expand_instruction(self, instruction, start_location):
        return [["COPY", "TSHIFT", instruction[2], start_location+1],
                ["ADD", "TSHIFT", "ON", start_location+2], ["ON", "TSHIFT", start_location+5],
                ["DIV", instruction[1], "SHC1", start_location+4], ["Z", "Z", start_location+2]]


class COPYPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "COPY"

    def expand_instruction(self, instruction, start_location):
        return [[instruction[2], "TCOPY1", start_location+1], ["TCOPY1", "TCOPY2", start_location+2],
                ["MOVE", instruction[1], "TCOPY2", start_location+3], ["TCOPY1", "TCOPY1", start_location+4],
                ["TCOPY2", "TCOPY2", start_location+5]]


class ANDPseudoInstruction(KuugaPseudoInstruction):

    @property
    def name(self):
        return "AND"

    def expand_instruction(self, instruction, start_location):
        return [
            # Set Up
            ["COPY", "TAND1", "ANDC1", start_location+1],
            ["COPY", "TAND7", instruction[2], start_location+2],
            # Main
            ["ON", "TAND1", start_location+18],
            ["COPY", "TAND2", instruction[1], start_location+4],
            ["COPY", "TAND3", instruction[2], start_location+5],
            ["ADD", "TAND4", "TAND4", start_location+6],
            ["ANDC2", "TAND2", start_location+12],
            ["ANDC2", "TAND3", start_location+15],
            # Operation
            ["ADD", "TAND4", "ON", start_location+9],
            ["ADD", instruction[1], instruction[1], start_location+10],
            ["ADD", instruction[2], instruction[2], start_location+11],
            ["Z", "Z", start_location+2],
            # Zero Check
            ["TAND5", "TAND5", start_location+13],
            ["TAND2", "TAND5", start_location+7],
            ["TAND5", "TAND5", start_location+9],
            # Zero Check2
            ["TAND6", "TAND6", start_location+16],
            ["TAND3", "TAND6", start_location+8],
            ["TAND6", "TAND6", start_location+9],
            # Cleanup
            ["MOVE", instruction[1], "TAND4", start_location+19],
            ["MOVE", instruction[2], "TAND7", start_location+20],
            ["TAND1", "TAND1", start_location+21],
            ["TAND2", "TAND2", start_location+22],
            ["TAND3", "TAND3", start_location+23],
            ["TAND4", "TAND4", start_location+24]
        ]


class Gouram(object):

    pseudo_instructions = {c().name: c() for c in KuugaPseudoInstruction.__subclasses__()}
    raw_file_reader = RawFileReader()

    def expand(self, file_name):
        with open(file_name, 'r') as description_file:
            file_string = description_file.read()
        program = self.raw_file_reader.split_data_and_code(file_string)
        program = self.process_program_object(program)
        return self.create_memory_contents(program)

    def process_program_object(self, program):
        expanded_code = self.expand_code(program.code)
        program_counter = len(expanded_code)
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
        return "{ " + ", ".join(result) + " }"

    @staticmethod
    def codeline_to_hexadecimal(codeline, data):
        first_op = data[codeline[0]][0]
        second_op = data[codeline[1]][0]
        third_op = codeline[2]
        binary_string = "{0}{1}{2}00".format(format(first_op, "010b"), format(second_op, "010b"),
                                             format(third_op, "010b"))
        return format(int(binary_string, base=2), "#010x")

    def expand_code(self, code):
        expanded_code = code
        while True:
            end_of_loop = True
            for counter, code_line in enumerate(expanded_code):
                if code_line[0] in self.pseudo_instructions.keys():
                    destinations_to_alter = [destination for destination, x in enumerate(expanded_code)
                                             if x[-1] > counter and destination != counter]
                    expansion = self.pseudo_instructions[code_line[0]].expand_instruction(code_line, counter)
                    for destination in destinations_to_alter:
                        expanded_code[destination][-1] += (len(expansion) - 1)
                    expanded_code = expanded_code[:counter] + expansion + expanded_code[counter+1:]
                    end_of_loop = False
                    break
            if end_of_loop:
                break
        return expanded_code


if __name__ == "__main__":
    g = Gouram()
    print(g.expand(sys.argv[1]))
