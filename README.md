# plunge

## Install

```shell
cd src && make
```


## Test

```shell
cd tests && make && python3 -m unittest -v
```


## Usage

```shell
$ ./plunge -h
Usage: plunge COMMAND

Options:
  -r, --run_file_name*     string      The program file to be run
  -i, --in_file_name       string      Redirect this file to the program's standard input stream
  -o, --out_file_name      string      Redirect the program's standard output stream to this file
  -e, --err_file_name      string      Redirect the program's standard error stream to this file
  -t, --max_cpu_time       integer     Maximum CPU time available for program execution (ms)
  -T, --max_real_time      integer     Maximum real time available for program operation (ms)
  -m, --max_memory         integer     Maximum memory available for program execution (kb)
  -u, --uid                integer     User id when the program runs
  -g, --gid                integer     Group id when the program runs
  -a, --args               string      Program running arguments, Can be set multiple times
      --max_stack          integer     Maximum stack space available for program execution (kb)
      --max_output_size    integer     The maximum file size a program can create (byte)
      --show                           Print specific restrictions

```

```shell
$ ./plunge -r ls -a -l
total 96
-rw-r--r--  1 meik  staff     97 Apr 29 11:06 Makefile
-rw-r--r--  1 meik  staff     68 Apr 29 11:27 limit.c
-rw-r--r--  1 meik  staff    144 Apr 29 11:28 limit.h
-rwxr-xr-x  1 meik  staff  13604 Apr 29 16:53 plunge
-rw-r--r--  1 meik  staff   9030 Apr 29 16:41 plunge.c
-rw-r--r--  1 meik  staff   1720 Apr 29 16:53 run.c
-rw-r--r--  1 meik  staff    843 Apr 29 14:31 run.h

cpu_time:  2 ms
real_time: 3 ms
memory:    3300 kb
exit_code: 0
signal:    0
status:    0
```