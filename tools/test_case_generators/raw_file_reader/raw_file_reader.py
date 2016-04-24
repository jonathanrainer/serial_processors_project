import re


class RawFileReader(object):
    """
    A class that controls taking a test case file and splitting apart the
    code and data from each other so they can be dealt with separately.
    """

    @staticmethod
    def split_data_and_code(file_name):
        """
        Takes the given test case file and splits out the code and data.
        :param file_name: The name of the test case file to considered
        :return: A Program object that contains the data as a dictionary of key-
        value pairs and the code as a list of code lines with line numbers
        attached.
        """
        # Open the given raw file name and read the whole file into one long
        # string.
        with open(file_name, 'r') as description_file:
            file_string = description_file.read()
        # Search the string for all the information that appears between the
        # DATA: and END_DATA tags.
        data_string = re.search("(?<=DATA:\n).*(?=END_DATA\n)",
                                file_string, re.DOTALL).group(0)
        # Take each key value pair, split it at the colon and store is as a
        # list of two element lists
        data_list = [re.split(": ", y) for y in
                     [x for x in re.split("\n", data_string) if len(x) > 0]]
        # Assert that all the sublists should be 2 elements in length
        assert([x for x in data_list if len(x) != 2] == [])
        # Create a dictionary by enumerating the data_list to add memory
        # locations to each piece of data. The key here is the name of the
        # piece of data, used later to match up locations in instructions
        # and the value is a list of the location and value of this piece of
        # data.
        data_dict = {data_pair[0]: [location, int(data_pair[1], base=16)]
                     for location, data_pair in enumerate(data_list)}
        # Extract all the code between the CODE: and END_CODE tags
        code_string = re.search("(?<=CODE:\n).*(?=END_CODE)", file_string,
                                re.DOTALL).group(0)
        # Split up each list of code into a list of code elements as well as a
        # location at the end of the list.
        code_list = [re.split(" ", y) + [count+1] for count, y in
                     enumerate([x for x in re.split("\n", code_string)
                                if len(x) > 0])]
        # Return a program object that has the data dictionary and the code list
        # stored within it.
        return Program(data_dict, code_list)


class Program(object):

    data = {}
    code = []

    def __init__(self, data_dict, code_list):
        """
        Initialise the object to hold the data given in the constructor.
        :param data_dict: A dictionary of names of data values, that map to
         their location and the value of that piece of data, as specified in
         the test case file.
        :param code_list: A list of each line of code, separated into elements,
        along with a line number for each code line.
        :return: Nothing
        """
        self.data = data_dict
        self.code = code_list
