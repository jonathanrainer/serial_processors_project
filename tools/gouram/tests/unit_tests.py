import unittest
from tools.gouram.gouram import Gouram

class GouramUnitTests(unittest.TestCase):

    def setUp(self):
        self.gouram = Gouram()

    def test_add_expand(self):
        expanded_code = self.gouram.expand_code([["ADD", "S1", "S2", 1]])
        self.assertListEqual(expanded_code, [["S2", "Z", 1], ["Z", "S1", 2], ["Z", "Z", 3]])

    def test_subtract_expand(self):
        expanded_code = self.gouram.expand_code([["SUB", "S1", "S2", 1]])
        self.assertListEqual(expanded_code, [["S2", "S1", 1]])

    def test_not_expand(self):
        expanded_code = self.gouram.expand_code([["NOT", "S1", 1]])
        self.assertListEqual(expanded_code, [['S1', 'Z', 1], ['ON', 'Z', 2], ['Z', 'Z', 3]])

    def test_multiply(self):
        expanded_code = self.gouram.expand_code([["MUL", "S3", "S4", 1]])
        self.assertListEqual(expanded_code, [["ON", "S4", 5],
                                             ["S3", "Z", 2], ["Z", "T1", 3], ["Z", "Z", 4],
                                             ["Z", "Z", 0], ["S3", "S3", 6], ["T1", "Z", 7], ["Z", "S3", 8],
                                             ["Z", "Z", 9], ["T1", "T1", 10]])

    def test_divide(self):
        expanded_code = self.gouram.expand_code([["DIV", "S6", "S7", 1]])
        self.assertListEqual(expanded_code, [["S7", "S6", 5],
                                             ["ON", "Z", 2], ["Z", "T1", 3], ["Z", "Z", 4],
                                             ["Z", "Z", 0], ["S6", "S6", 6], ["T1", "Z", 7], ["Z", "S6", 8],
                                             ["Z", "Z", 9], ["T1", "T1", 10]])

if __name__ == '__main__':
    unittest.main()
