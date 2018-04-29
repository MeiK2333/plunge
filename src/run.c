#include <sys/time.h>
#include <sys/wait.h>

#include "run.h"

void run(const struct config *_config, struct result *_result) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    set_limit(_config);

    pid_t pid = fork();

    if (pid < 0) {
        RUN_ERR_EXIT("fork failure!");
    } else if (pid == 0) {
        set_limit(_config);
        execvp(_config->run_file_name, _config->args);
        RUN_ERR_EXIT("exec failure!");
    } else if (pid > 0) {
        if (wait4(pid, &_result->status, WSTOPPED, &_result->_rusage) == -1) {
            RUN_ERR_EXIT("wait4 failure!");
        }
    }
}