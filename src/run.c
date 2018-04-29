#include <sys/time.h>
#include <sys/wait.h>

#include "run.h"

void init_result(struct result *_result) {
    _result->exit_code = _result->signal = _result->status = 0;
    _result->real_time = _result->cpu_time = _result->memory = 0;
}

void run(const struct config *_config, struct result *_result) {
    init_result(_result);
    set_limit(_config);

    struct timeval start, end;
    /* Start recording time */
    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid < 0) {
        RUN_ERR_EXIT("fork failure!");
    } else if (pid == 0) {
        /* set limit */
        set_limit(_config);
        execvp(_config->run_file_name, _config->args);
        RUN_ERR_EXIT("exec failure!");
    } else if (pid > 0) {
        if (wait4(pid, &_result->status, WSTOPPED, &_result->_rusage) == -1) {
            RUN_ERR_EXIT("wait4 failure!");
        }

        /* get real time */
        gettimeofday(&end, NULL);
        _result->real_time = (long) ((end.tv_sec * 1000 + end.tv_usec / 1000) - (start.tv_sec * 1000 +
                                                                                 start.tv_usec / 1000));

        /* get resource usage */
        _result->cpu_time = (long) (_result->_rusage.ru_utime.tv_sec * 1000
                                    + _result->_rusage.ru_utime.tv_usec / 1000
                                    + _result->_rusage.ru_stime.tv_sec * 1000
                                    + _result->_rusage.ru_stime.tv_usec / 1000);
        _result->memory = _result->_rusage.ru_maxrss;
        if (WIFSIGNALED(_result->status) != 0) {
            _result->signal = WTERMSIG(_result->status);
        }
        _result->exit_code = WEXITSTATUS(_result->status);
    }
}