#ifndef TESTS_H
#define TESTS_H

#include <pthread.h>
#include <time.h>

#define ITERATIONS 1000
#define BUFFER_SIZE 2048
#define MAX_THREADS 25

typedef void (*void_ptr)();

static void
die(const char * error);

void *
test_buffer_write();

static int
run(int threadnum, void (*f)(void) );

#endif
