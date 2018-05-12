#ifndef PLUNGE_RUN_H
#define PLUNGE_RUN_H

#define ARGS_MAX_NUMBER 256

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "limit.h"

struct config {
    long max_cpu_time;
    long max_real_time;
    long max_memory;
    long max_stack;
    long max_output_size;
    long max_process;
    uid_t uid;
    gid_t gid;

    int memory_limit;
    int show;

    char *args[ARGS_MAX_NUMBER];
    char *run_file_name;
    char *in_file_name;
    char *out_file_name;
    char *err_file_name;
};

struct result {
    struct rusage _rusage;
    long cpu_time;
    long real_time;
    long memory;
    int signal;
    int status;
    int exit_code;
};

#define UNLIMITED 0

#define RUN_ERR_EXIT(err_msg) {fprintf(stderr, "RUN_ERR_EXIT: " # err_msg "\n"); exit(EXIT_FAILURE);}

void run(const struct config *, struct result *);

#endif //PLUNGE_RUN_H
