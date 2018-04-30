import os
import unittest

from plunge import Plunge


class TestLimit(unittest.TestCase):

    def test_cpu_time_limit(self):
        run_file_name = './cpu_time_out.out'
        max_cpu_time = 100
        p = Plunge(run_file_name=run_file_name, max_cpu_time=max_cpu_time)
        p.run()
        self.assertTrue(p.parser_data['cpu_time'] < 2000)

    def test_real_time_limit(self):
        run_file_name = './real_time_out.out'
        max_real_time = 100
        p = Plunge(run_file_name=run_file_name, max_real_time=max_real_time)
        p.run()
        self.assertTrue(p.parser_data['real_time'] < 500)

    def test_output_size_limit(self):
        run_file_name = './output_size_out.out'
        max_output_size = 1024
        out_file = 'tmp.out'
        p = Plunge(run_file_name=run_file_name, max_output_size=max_output_size, out_file_name=out_file)
        p.run()
        self.assertEqual(p.parser_data['signal'], 25)


if __name__ == '__main__':
    unittest.main()
