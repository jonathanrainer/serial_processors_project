from tools.gouram.gouram import Gouram
import unittest


class GouramIntegrationTests(unittest.TestCase):

    gouram = None

    def setUp(self):
        self.gouram = Gouram()

    def test_assert_fail_output_is_as_expected(self):
        file = "test_cases/___assert_fail--00.sam"
        self.assertEqual("{ 0x0180A004, 0x2809008, 0x280A00C, 0x00000001 0x00000025, 0x00000032,0x000000054F, "
                         "0x00000000, 0x00000010, 0x00000000}", self.gouram.expand(file))

if __name__ == '__main__':
    unittest.main()
