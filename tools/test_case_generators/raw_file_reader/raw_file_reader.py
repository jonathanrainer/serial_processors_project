from tools.test_case_generators.raw_file_reader.program import Program
import re

class RawFileReader(object):

    @staticmethod
    def split_data_and_code(file_string):
        data_string = re.search("(?<=DATA:\n).*(?=END_DATA\n)", file_string, re.DOTALL).group(0)
        data_list = [re.split(": ", y) for y in [x for x in re.split("\n", data_string) if len(x) > 0]]
        assert([x for x in data_list if len(x) != 2] == [])
        data_dict = {data_pair[0]: [location, int(data_pair[1], base=16)]
                     for location, data_pair in enumerate(data_list)}
        code_string = re.search("(?<=CODE:\n).*(?=END_CODE)", file_string, re.DOTALL).group(0)
        code_list = [re.split(" ", y) + [count+1] for count, y in
                     enumerate([x for x in re.split("\n", code_string) if len(x) > 0])]
        return Program(data_dict, code_list)