#include "main.h"
#include "tests.h"

char * program_name;

void
die(const char * error){

    if ( !strcmp(error, "") ){
      fprintf(stderr, "%s: %s\n", program_name, error);
    }

    printf("%s [test]"
           "\navailable tests:"
           "\n singlethread\n multithread\n mutex\n all\n",
           program_name);

    exit(1);
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
        printf("singlethread");
      }

      if ( !strcmp(argv[i], "multithread") ) {
        printf("multithread");
      }

      if ( !strcmp(argv[i], "mutex") ) {
        printf("mutex");
      }

      if ( !strcmp(argv[i], "all") ) {
        printf("all");
      }

    }
    return 0;
}
