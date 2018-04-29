import unittest

from plunge import Plunge


class TestParame(unittest.TestCase):

    def test_run_file_name(self):
        run_file_name = 'ls'
        p = Plunge(run_file_name=run_file_name, show=True)
        p.run()
        self.assertEqual(run_file_name, p.parser_data['run_file_name'])

    def test_in_file_name(self):
        run_file_name = 'ls'
        in_file_name = 'test.in'
        p = Plunge(run_file_name=run_file_name, show=True, in_file_name=in_file_name)
        p.run()
        self.assertEqual(in_file_name, p.parser_data['in_file_name'])

    def test_out_file_name(self):
        run_file_name = 'ls'
        out_file_name = 'test.in'
        p = Plunge(run_file_name=run_file_name, show=True, out_file_name=out_file_name)
        p.run()
        self.assertEqual(out_file_name, p.parser_data['out_file_name'])

    def test_err_file_name(self):
        run_file_name = 'ls'
        err_file_name = 'test.in'
        p = Plunge(run_file_name=run_file_name, show=True, err_file_name=err_file_name)
        p.run()
        self.assertEqual(err_file_name, p.parser_data['err_file_name'])

    def test_max_cpu_time(self):
        run_file_name = 'ls'
        max_cpu_time = 1000
        p = Plunge(run_file_name=run_file_name, show=True, max_cpu_time=max_cpu_time)
        p.run()
        self.assertEqual(max_cpu_time, p.parser_data['max_cpu_time'])

    def test_max_read_time(self):
        run_file_name = 'ls'
        max_real_time = 1000
        p = Plunge(run_file_name=run_file_name, show=True, max_real_time=max_real_time)
        p.run()
        self.assertEqual(max_real_time, p.parser_data['max_real_time'])

    def test_max_memory(self):
        run_file_name = 'ls'
        max_memory = 1000
        p = Plunge(run_file_name=run_file_name, show=True, max_memory=max_memory)
        p.run()
        self.assertEqual(max_memory, p.parser_data['max_memory'])

    def test_args(self):
        run_file_name = 'ls'
        args = ['-l', '.']
        p = Plunge(run_file_name=run_file_name, show=True, args=args)
        p.run()
        args_str = '[' + " '{}',".format(run_file_name)
        for arg in args:
            args_str += " '{}',".format(arg)
        args_str += ']'
        self.assertEqual(args_str, p.parser_data['args'])

    def test_max_stack(self):
        run_file_name = 'ls'
        max_stack = 655350
        p = Plunge(run_file_name=run_file_name, show=True, max_stack=max_stack)
        p.run()
        self.assertEqual(max_stack, p.parser_data['max_stack'])

    def test_max_output_size(self):
        run_file_name = 'ls'
        max_output_size = 655350
        p = Plunge(run_file_name=run_file_name, show=True, max_output_size=max_output_size)
        p.run()
        self.assertEqual(max_output_size, p.parser_data['max_output_size'])


if __name__ == '__main__':
    unittest.main()
