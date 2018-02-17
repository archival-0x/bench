#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bench.h"

char * program_name;
clock_t start, end;


////////////
/* IOPS CPU-bound stack-based buffer write

Description:
  Utilizing a writable buffer for benchmarking. Flexible for
  single and multi-threaded support. Configurable constants
  are ITERATIONS and BUFFER_SIZE.

Execution Process:
 * 1. Create a cycle
 * 2. For each element of the array, set to arbitrary value
 * 3. Re-run, NULL each element
 * 4. Finish benchmark, output IOPS result
*/
////////////
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

  // Start the clock. Ensure that absolutely no other operation except for the
  // iteration is occuring!
  start = clock();

  for ( cycles = 0; cycles <= ITERATIONS; cycles++ ){
    for ( i = 0; i <= BUFFER_SIZE; i++ ){
      for ( j = 0; j <= BUFFER_SIZE; j++){
        mem_array[j] = 10000000;
      }
      mem_array[i] = (int*) NULL;
    }
  }

  // Stop the clock. We can now continue the analysis.
  end = clock();

  benchmark = ( end - start ) / ( CLOCKS_PER_SEC / 1000 );


  fprintf(stdout, "\nRun-time Execution: %i ms\n", benchmark);

  /* is this good behavior? :uneasy_face: */
  pthread_exit( NULL);
  return NULL;
}

static void
die(const char * error)
{

  if ( !strcmp(error, "") ){
    fprintf(stderr, "%s: %s\n", program_name, error);
  }

  printf("%s [test]"
         "\navailable tests:"
         "\n - singlethread\n - multithread\n",
         program_name);

  exit(1);
}

static int
run(int threadnum, void (*f)(void) )
{
    int bench_result;
    register int t;
    pthread_t tid;

    /* kill if thread count is 0 */
    if (threadnum == 0) {
      die("thread count cannot be 0");
    }

    /* create our threads */
    for (t = 0; t < threadnum; t++ ){
      pthread_create(&tid, NULL, (void *)(*f), NULL);
      pthread_join(tid, NULL);
    }
}

int
main( int argc, char **argv )
{
  register int i;
  program_name = argv[0];


  // Only one test at a time!
  if ( argc < 2 || argc > 2 )
  {
      die("incorrect provision of arguments.");
  }

  // Argparse
  for (i = 0; i < argc; i ++){

    if ( !strcmp(argv[i], "singlethread") )
    {

      fprintf(stdout, "==\tEXECUTION\t==\n TEST: Single-threaded stack-based buffer-write\n");
      run(1, (void *) test_buffer_write);

    }

    if ( !strcmp(argv[i], "multithread") )
    {

      fprintf(stdout, "==\tEXECUTION\t==\n TEST: Multi-threaded stack-based buffer-write\n");
      run(MAX_THREADS, (void *) test_buffer_write);

    }

  }

  fprintf(stdout, "\n==\tCOMPLETE\t==\n");

  return 0;
}
