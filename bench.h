#ifndef TESTS_H
#define TESTS_H

#include <pthread.h>
#include <time.h>

#define ITERATIONS 1000
#define BUFFER_SIZE 2048
#define MAX_THREADS 25

typedef void (*void_ptr)();

void *
test_buffer_write();

#endif
