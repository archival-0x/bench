#ifndef TESTS_H
#define TESTS_H

#include <time.h>
#include <pthread.h>

#define ITERATIONS 100000

clock_t start, end;

void *
test_singlethread();

void *
test_multithread();

void *
test_mutex();

#endif
