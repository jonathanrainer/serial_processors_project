import unittest

from test_case_generators.gouram import Gouram


class GouramUnitTests(unittest.TestCase):

    def setUp(self):
        self.gouram = Gouram()

    def test_add_expand(self):
        expanded_code = self.gouram.expand_code([["ADD", "S1", "S2", 1]])
        self.assertListEqual(expanded_code, [["S2", "TADD", 1], ["TADD", "S1", 2], ["TADD", "TADD", 3]])

    def test_subtract_expand(self):
        expanded_code = self.gouram.expand_code([["SUB", "S1", "S2", 1]])
        self.assertListEqual(expanded_code, [["S2", "S1", 1]])

    def test_not_expand(self):
        expanded_code = self.gouram.expand_code([["NOT", "S1", 1]])
        self.assertListEqual(expanded_code, [['S1', 'TNOT', 1], ['ON', 'TNOT', 2], ['S1', 'S1', 3],
                                             ['TNOT', 'TMOVE', 4], ['TMOVE', 'S1', 5], ['TMOVE', 'TMOVE', 6],
                                             ['TNOT', 'TNOT', 7]])

    def test_multiply(self):
        expanded_code = self.gouram.expand_code([["MUL", "S3", "S4", 1]])
        self.assertListEqual(expanded_code, [["ON", "S4", 5],
                                             ["S3", "TADD", 2], ["TADD", "TMUL", 3], ["TADD", "TADD", 4],
                                             ["Z", "Z", 0], ["TMUL", "TADD", 6], ["TADD", "S3", 7],
                                             ["TADD", "TADD", 8], ["TMUL", "TMUL", 9]])

    def test_divide(self):
        expanded_code = self.gouram.expand_code([["DIV", "S6", "S7", 1]])
        self.assertListEqual(expanded_code, [["S7", "S6", 5], ["ON", "TADD", 2], ["TADD", "TDIV", 3],
                                             ["TADD", "TADD", 4], ["Z", "Z", 0], ["S6", "S6", 6], ["TDIV", "TMOVE", 7],
                                             ["TMOVE", "S6", 8], ["TMOVE", "TMOVE", 9], ["TDIV", "TDIV", 10]])

    def test_shift_right(self):
        expanded_code = self.gouram.expand_code([["SHR", "S2", "S3", 1]])
        self.assertListEqual(expanded_code, [[]])

    def test_shift_left(self):
        expanded_code = self.gouram.expand_code([["SHL", "S2", "S3", 1]])
        self.assertListEqual(expanded_code, [[]])

if __name__ == '__main__':
    unittest.main()
