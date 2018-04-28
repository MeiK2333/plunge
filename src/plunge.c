#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "limit.h"

static const char *opt_string = "r:t:T:m:i:o:e:g:u:h?";

static const struct option long_opts[] = {
        {"max_cpu_time",    required_argument, NULL, 't'},
        {"max_real_time",   required_argument, NULL, 'T'},
        {"max_memory",      required_argument, NULL, 'm'},
        {"run_file_name",   required_argument, NULL, 'r'},
        {"in_file_name",    required_argument, NULL, 'i'},
        {"out_file_name",   required_argument, NULL, 'o'},
        {"err_file_name",   required_argument, NULL, 'e'},
        {"uid",             required_argument, NULL, 'u'},
        {"gid",             required_argument, NULL, 'g'},
        {"max_stack",       required_argument, NULL, 0},
        {"max_output_size", required_argument, NULL, 0},
        {"args",            required_argument, NULL, 0},
        {"env",             required_argument, NULL, 0},
        {"show",            no_argument,       NULL, 0},
        {NULL,              no_argument,       NULL, 0}
};

/*
 * Display program usage, and exit.
 */
void display_usage();

/*
 * Display program config
 */
void display_config(struct config);

void assert_str_to(const char *str_to) {
    if (str_to[0] != 0) {
        display_usage();
    }
}

int main(int argc, char *argv[]) {
    int opt = 0;
    int long_index = 0;
    int arg_cnt = 0;
    int env_cnt = 0;
    int run_flag = 0;

    int show = 0;
    opterr = 0;
    char *str_to;

    struct config _config;
    _config.max_cpu_time = _config.max_real_time = _config.max_memory = _config.max_output_size = _config.max_stack = -1;
    _config.uid = _config.gid = 0;
    _config.memory_limit = 0;
    _config.args[0] = _config.env[0] = NULL;
    _config.run_file_name = _config.in_file_name = _config.out_file_name = _config.err_file_name = NULL;

    while ((opt = getopt_long(argc, argv, opt_string, long_opts, &long_index)) != -1) {
        switch (opt) {
            case 'r':
                _config.run_file_name = optarg;
                run_flag = 1;
                break;
            case 't':
                _config.max_cpu_time = strtol(optarg, &str_to, 10);
                assert_str_to(str_to);
                break;
            case 'T':
                _config.max_real_time = strtol(optarg, &str_to, 10);
                assert_str_to(str_to);
                break;
            case 'm':
                _config.max_memory = strtol(optarg, &str_to, 10);
                assert_str_to(str_to);
                _config.memory_limit = 1;
                break;
            case 'i':
                _config.in_file_name = optarg;
                break;
            case 'o':
                _config.out_file_name = optarg;
                break;
            case 'e':
                _config.err_file_name = optarg;
                break;
            case 'g':
                _config.gid = (gid_t) strtoul(optarg, &str_to, 10);
                assert_str_to(str_to);
                break;
            case 'u':
                _config.uid = (uid_t) strtoul(optarg, &str_to, 10);
                assert_str_to(str_to);
                break;
            case 'h':
            case '?':
                display_usage();
                break;
            case 0:
                if (strcmp("env", long_opts[long_index].name) == 0) {
                    _config.env[env_cnt++] = optarg;
                } else if (strcmp("args", long_opts[long_index].name) == 0) {
                    _config.args[arg_cnt++] = optarg;
                } else if (strcmp("max_stack", long_opts[long_index].name) == 0) {
                    _config.max_stack = strtol(optarg, &str_to, 10);
                    assert_str_to(str_to);
                    _config.memory_limit = 1;
                } else if (strcmp("max_output_size", long_opts[long_index].name) == 0) {
                    _config.max_output_size = strtol(optarg, &str_to, 10);
                    assert_str_to(str_to);
                } else if (strcmp("show", long_opts[long_index].name) == 0) {
                    show = 1;
                }
                break;
            default:
                display_usage();
                break;
        }
    }

    if (!run_flag) {
        display_usage();
    }

    _config.env[env_cnt] = NULL;
    _config.args[arg_cnt] = NULL;

    if (show) {
        display_config(_config);
    }

    return EXIT_SUCCESS;
}

void display_usage() {
    char *usage = ""
            "Usage: plunge COMMAND\n"
            "\n"
            "Options:\n"
            "  -r, --run_file_name*     string      The program file to be run\n"
            "  -i, --in_file_name       string      Redirect this file to the program's standard input stream\n"
            "  -o, --out_file_name      string      Redirect the program's standard output stream to this file\n"
            "  -e, --err_file_name      string      Redirect the program's standard error stream to this file\n"
            "  -t, --max_cpu_time       integer     Maximum CPU time available for program execution (ms)\n"
            "  -T, --max_real_time      integer     Maximum real time available for program operation (ms)\n"
            "  -m, --max_memory         integer     Maximum memory available for program execution (byte)\n"
            "  -u, --uid                integer     User id when the program runs\n"
            "  -g, --gid                integer     Group id when the program runs\n"
            "      --max_stack          integer     Maximum stack space available for program execution (byte)\n"
            "      --max_output_size    integer     The maximum file size a program can create (byte)\n"
            "      --args               string      Program running arguments, Can be set multiple times\n"
            "      --env                string      Program running environment variables, Can be set multiple times\n"
            "      --show                           Print specific restrictions\n"
            "\n";
    fprintf(stderr, "%s", usage);
    exit(EXIT_FAILURE);
}

void display_config(const struct config _config) {
    fprintf(stderr, "run_file_name:   %s\n", _config.run_file_name);
    fprintf(stderr, "args:            ");
    fprintf(stderr, "[");
    for (int i = 0; _config.args[i] != NULL; i++) {
        fprintf(stderr, " '%s',", _config.args[i]);
    }
    fprintf(stderr, "]\n");
    fprintf(stderr, "env:             ");
    fprintf(stderr, "[");
    for (int i = 0; _config.env[i] != NULL; i++) {
        fprintf(stderr, " '%s',", _config.env[i]);
    }
    fprintf(stderr, "]\n");
    fprintf(stderr, "in_file_name:    %s\n", _config.in_file_name);
    fprintf(stderr, "out_file_name:   %s\n", _config.out_file_name);
    fprintf(stderr, "err_file_name:   %s\n", _config.err_file_name);
    fprintf(stderr, "max_cpu_time:    %ld\n", _config.max_cpu_time);
    fprintf(stderr, "max_real_time:   %ld\n", _config.max_real_time);
    fprintf(stderr, "max_memory:      %ld\n", _config.max_memory);
    fprintf(stderr, "max_stack:       %ld\n", _config.max_stack);
    fprintf(stderr, "max_output_size: %ld\n", _config.max_output_size);
    fprintf(stderr, "gid:             %u\n", _config.gid);
    fprintf(stderr, "uid:             %u\n", _config.uid);
}