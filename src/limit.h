#ifndef PLUNGE_LIMIT_H
#define PLUNGE_LIMIT_H

#define ARGS_MAX_NUMBER 256
#define ENV_MAX_NUMBER 256

#include <unistd.h>

struct config {
    long max_cpu_time;
    long max_real_time;
    long max_memory;
    long max_stack;
    long max_output_size;
    uid_t uid;
    gid_t gid;

    int memory_limit;

    char *args[ARGS_MAX_NUMBER];
    char *env[ENV_MAX_NUMBER];
    char *run_file_name;
    char *in_file_name;
    char *out_file_name;
    char *err_file_name;
};

#endif //PLUNGE_LIMIT_H
