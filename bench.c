#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <time.h>
#include <signal.h>
#include <pthread.h>

#define ITERATIONS 1000
#define BUFFER_SIZE 2048
#define MAX_THREADS 25

/* create a type alias so that we can
 * efficiently pass pointers into functions */
typedef void (*void_ptr)();

static char * program_name;
static clock_t start, end;

/* global mutex lock */
static pthread_mutex_t lock;

/* globals for increments before average */
static float global_counter = 0;
static int thread_completes = 0;


static void
die(const char * error)
{
    if (!strcmp(error, ""))
      fprintf(stderr, "%s: %s\n", program_name, error);

    fprintf(stdout, "%s [test]"
           "\navailable tests:"
           "\n - singlethread\n - multithread\n",
           program_name);

    exit(EXIT_FAILURE);
}



static void
sig_handler(int sig)
{
    if (sig != SIGINT)
        exit(EXIT_FAILURE);

    float sig_result;
    fprintf(stderr, "\n==\tKILLED\t==\n");

    /* calculate average before death */
    sig_result = global_counter / (float) thread_completes;
    fprintf(stderr, "\n\n[FINAL] Average for %i threads of execution: %.6f ms\n", thread_completes, sig_result);
    exit(EXIT_FAILURE);
}


/* IOPS CPU-bound stack-based buffer write
 *
 *   Description:
 *     Utilizing a writable buffer for benchmarking. Flexible for
 *     single and multi-threaded support. Configurable constants
 *     are ITERATIONS and BUFFER_SIZE.
 *
 *   Execution Process:
 *    1. Create a cycle
 *    2. For each element of the array, set to arbitrary value
 *    3. Re-run, NULL each element
 *    4. Finish benchmark, output IOPS result
 */
void *
test_buffer_write()
{
    /* local register integers for iteration */
    register int i, j;
    register int cycles;

    /* the buffer we will be populating */
    int mem_array[BUFFER_SIZE] = {};

    /* represents benchmarked time */
    int benchmark;


    ////////////////////////////////////////////////////////
    start = clock();

    for (cycles = 0; cycles <= ITERATIONS; cycles++){
      for (i = 0; i <= BUFFER_SIZE; i++) {
        for (j = 0; j <= BUFFER_SIZE; j++)
            mem_array[j] = 10000000;

        mem_array[i] = (int*) NULL;
      }
    }

    end = clock();
    ////////////////////////////////////////////////////////


    /* lock critical section */
    pthread_mutex_lock(&lock);

    /* calculate the benchmark and increment counters */
    benchmark = ( end - start ) / ( CLOCKS_PER_SEC / 1000 );
    global_counter += (float) benchmark;
    thread_completes++;

    /* unlock critical section */
    pthread_mutex_unlock(&lock);

    /* output */
    fprintf(stdout, "[Job %ld] Run-time Execution Benchmark: %i ms\n", pthread_self(), benchmark);

    /* terminate the thread */
    pthread_exit(NULL);
}


static float
run(int threadnum, void (*f)(void) )
{
    float bench_result;
    register int a, b;
    pthread_t tid;

    signal(SIGINT, sig_handler);

    /* kill if thread count is 0 */
    if (threadnum == 0)
        die("thread count cannot be 0");

    /* create our threads and join up */
    for ( a = 0; a < threadnum; a++ ){
        pthread_create(&tid, NULL, (void *)(*f), NULL);
        sleep(1);
        pthread_join(tid, NULL);
    }

    /* calculate a final average */
    bench_result = global_counter / (float) thread_completes;
    return bench_result;
}


int
main(int argc, char **argv)
{
    register int i;
    float final_result;

    program_name = argv[0];

    /* one test at a time! */
    if (argc < 2 || argc > 2)
        die("incorrect provision of arguments.");


    /* perform simple argument parsing */
    for (i = 0; i < argc; i ++) {

        fprintf(stdout, "==\tEXECUTION\t==\nTEST: ");
        if (!strcmp(argv[i], "singlethread")) {
            fprintf(stdout, "Single-threaded stack-based buffer-write\n");
            final_result = run(1, (void *) test_buffer_write);
        } else if (!strcmp(argv[i], "multithread")) {
            fprintf(stdout, "Multi-threaded stack-based buffer-write\n");
            final_result = run(MAX_THREADS, (void *) test_buffer_write);
        }
    }

    /* success: print final average */
    fprintf(stdout, "\n==\tCOMPLETE\t==\n");
    fprintf(stdout, "\n\n[FINAL] Average for %i threads of execution: %.6f ms\n", thread_completes, final_result);
    return 0;
}
