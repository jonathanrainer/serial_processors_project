from tools.gouram.gouram import Gouram
import unittest


class GouramIntegrationTests(unittest.TestCase):

    gouram = None

    def setUp(self):
        self.gouram = Gouram()

    def test_assert_fail_output_is_as_expected(self):
        file = "test_cases/___assert_fail--00.sam"
        self.assertEqual("{ 0x0240b004, 0x02c06008, 0x02c0b00c, 0x00000001, 0x00000025, 0x00000032, 0x0000000c, "
                         "0x0000054f, 0x00000000, 0x00000010, 0x00000000, 0x00000000 }", self.gouram.expand(file))

if __name__ == '__main__':
    unittest.main()
