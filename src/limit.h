#ifndef PLUNGE_LIMIT_H
#define PLUNGE_LIMIT_H

#include "run.h"

struct config;

void set_limit(const struct config *);

void set_stream(const struct config *);

#define LIMIT_ERR_EXIT(err_msg) {fprintf(stderr, "LIMIT_ERR_EXIT: " # err_msg "\n"); exit(EXIT_FAILURE);}
#define STREAM_ERR_EXIT(err_msg) {fprintf(stderr, "STREAM_ERR_EXIT: " # err_msg "\n"); exit(EXIT_FAILURE);}

#endif //PLUNGE_LIMIT_H
