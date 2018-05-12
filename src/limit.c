#include "limit.h"

void set_limit(const struct config *_config) {
    struct rlimit rl;

    /* set cpu time limit (seconds) */
    if (_config->max_cpu_time != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) ((_config->max_cpu_time + 999) / 1000);
        if (setrlimit(RLIMIT_CPU, &rl) != 0) {
            LIMIT_ERR_EXIT("setrlimit RLIMIT_CPU failure!");
        }
    }

    /* set real time limit */
    if (_config->max_real_time != UNLIMITED) {
        struct itimerval rt;
        long t = _config->max_real_time;
        rt.it_interval.tv_sec = 0;
        rt.it_interval.tv_usec = 0;
        rt.it_value.tv_sec = t / 1000;
        rt.it_value.tv_usec = (int) (t % 1000) * 1000;
        if (setitimer(ITIMER_REAL, &rt, (struct itimerval *) 0) != 0) {
            LIMIT_ERR_EXIT("setitimer ITIMER_REAL failure!");
        }
    }

    /* set memory limit */
    /* if memory_limit == 0, only check usage number to prevent program crashes */
    if (_config->memory_limit != 0 && _config->max_memory != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) _config->max_memory;
        if (setrlimit(RLIMIT_AS, &rl) != 0) {
            LIMIT_ERR_EXIT("setrlimit RLIMIT_AS failure!");
        }
    }

    /* set stack limit */
    if (_config->memory_limit != 0 && _config->max_stack != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) _config->max_stack;
        if (setrlimit(RLIMIT_STACK, &rl) != 0) {
            LIMIT_ERR_EXIT("setrlimit RLIMIT_STACK failure!");
        }
    }

    /* set output size limit */
    if (_config->max_output_size != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) _config->max_output_size;
        if (setrlimit(RLIMIT_FSIZE, &rl) != 0) {
            LIMIT_ERR_EXIT("setrlimit RLIMIT_FSIZE failure!");
        }
    }

    /* set max process limit */
    if (_config->max_process != UNLIMITED) {
        rl.rlim_cur = rl.rlim_max = (rlim_t) _config->max_process;
        if (setrlimit(RLIMIT_NPROC, &rl) != 0) {
            LIMIT_ERR_EXIT("setrlimit RLIMIT_NPROC failure!");
        }
    }

    /* set gid */
    if (_config->gid != UNLIMITED) {
        if (setgid(_config->gid) == -1) {
            LIMIT_ERR_EXIT("setgid failure!");
        }
    }

    /* set uid */
    if (_config->uid != UNLIMITED) {
        if (setuid(_config->uid) == -1) {
            LIMIT_ERR_EXIT("setuid failure!");
        }
    }
}

void set_stream(const struct config *_config) {

    /* redirect in_file to stdin */
    if (_config->in_file_name != NULL) {
        FILE *in_file;
        if ((in_file = fopen(_config->in_file_name, "r")) == NULL) {
            STREAM_ERR_EXIT("fopen in_file failure!");
        }
        if (dup2(fileno(in_file), STDIN_FILENO) == -1) {
            STREAM_ERR_EXIT("dup2 in_file failure!");
        }
    }

    /* redirect stdout to out_file */
    if (_config->out_file_name != NULL) {
        FILE *out_file;
        if ((out_file = fopen(_config->out_file_name, "w")) == NULL) {
            STREAM_ERR_EXIT("fopen out_file failure!");
        }
        if (dup2(fileno(out_file), STDOUT_FILENO) == -1) {
            STREAM_ERR_EXIT("dup2 out_file failure!");
        }
    }

    /* redirect stderr to err_file */
    if (_config->err_file_name != NULL) {
        FILE *err_file;
        if ((err_file = fopen(_config->err_file_name, "w")) == NULL) {
            STREAM_ERR_EXIT("fopen err_file failure!");
        }
        if (dup2(fileno(err_file), STDERR_FILENO) == -1) {
            STREAM_ERR_EXIT("dup2 err_file failure!");
        }
    }
}