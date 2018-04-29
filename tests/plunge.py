# coding=utf-8
import os
import json
import subprocess


class Plunge(object):

    def __init__(self, run_file_name, in_file_name=None, out_file_name=None, err_file_name=None,
                 max_cpu_time=None, max_real_time=None, max_memory=None, uid=None, gid=None, args=None,
                 max_stack=None, max_output_size=None, show=None):
        if not os.path.exists("../src/plunge"):
            print("Please make first")
            exit(1)
        cmd = ['../src/plunge', '--run_file_name={run_file_name}'.format(run_file_name=run_file_name)]
        if args:
            assert isinstance(args, list)
            for arg in args:
                cmd.append('--arg={arg}'.format(arg=arg))
        if in_file_name:
            cmd.append('--in_file_name={in_file_name}'.format(in_file_name=in_file_name.strip()))
        if out_file_name:
            cmd.append('--out_file_name={out_file_name}'.format(out_file_name=out_file_name.strip()))
        if err_file_name:
            cmd.append('--err_file_name={err_file_name}'.format(err_file_name=err_file_name.strip()))
        if max_cpu_time:
            cmd.append('--max_cpu_time={max_cpu_time}'.format(max_cpu_time=max_cpu_time))
        if max_real_time:
            cmd.append('--max_real_time={max_real_time}'.format(max_real_time=max_real_time))
        if max_memory:
            cmd.append('--max_memory={max_memory}'.format(max_memory=max_memory))
        if uid:
            cmd.append('--uid={uid}'.format(uid=uid))
        if gid:
            cmd.append('--gid={gid}'.format(gid=gid))
        if max_stack:
            cmd.append('--max_stack={max_stack}'.format(max_stack=max_stack))
        if max_output_size:
            cmd.append('--max_output_size={max_output_size}'.format(max_output_size=max_output_size))
        if show:
            cmd.append('--show')
        self.cmd = cmd
        self.show = show
        self.parser_data = {}

    def run(self):
        proc = subprocess.Popen(self.cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        out, err = proc.communicate()
        self.out = bytes.decode(out)
        self.err = bytes.decode(err).strip()
        self.parser_err()

    def parser_err(self):
        if not self.show:
            err_data = self.err.split('\n')
            self.parser_data['cpu_time'] = int(err_data[0][11:-3])
            self.parser_data['real_time'] = int(err_data[1][11:-3])
            self.parser_data['memory'] = int(err_data[2][11:-5])
            self.parser_data['exit_code'] = int(err_data[3][11:])
            self.parser_data['signal'] = int(err_data[4][11:])
            self.parser_data['status'] = int(err_data[5][11:])
        else:
            err_data = self.err.split('\n')
            self.parser_data['run_file_name'] = err_data[0][17:]
            self.parser_data['args'] = err_data[1][17:]
            self.parser_data['in_file_name'] = err_data[2][17:]
            self.parser_data['out_file_name'] = err_data[3][17:]
            self.parser_data['err_file_name'] = err_data[4][17:]
            self.parser_data['max_cpu_time'] = int(err_data[5][17:-3])
            self.parser_data['max_real_time'] = int(err_data[6][17:-3])
            self.parser_data['max_memory'] = int(err_data[7][17:-5])
            self.parser_data['max_stack'] = int(err_data[8][17:-5])
            self.parser_data['max_output_size'] = int(err_data[9][17:-5])
            self.parser_data['gid'] = int(err_data[10][17:])
            self.parser_data['uid'] = int(err_data[11][17:])

            self.parser_data['cpu_time'] = int(err_data[13][11:-3])
            self.parser_data['real_time'] = int(err_data[14][11:-3])
            self.parser_data['memory'] = int(err_data[15][11:-5])
            self.parser_data['exit_code'] = int(err_data[16][11:])
            self.parser_data['signal'] = int(err_data[17][11:])
            self.parser_data['status'] = int(err_data[18][11:])


if __name__ == '__main__':
    p = Plunge('ls', args=['-l', '.'], show=True)
    p.run()
    print(json.dumps(p.parser_data, ensure_ascii=False, indent=4))
