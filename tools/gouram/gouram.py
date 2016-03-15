import re

class Gouram(object):

    def expand(self, file_name):
        with open(file_name, 'r') as description_file:
            file_string = description_file.read()
        program = self.split_data_and_code(file_string)

    def split_data_and_code(self, file_string):
        data_string =

class Program(object):

    data = None
    code = None

