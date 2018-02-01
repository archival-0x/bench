#include "main.h"
#include "tests.h"

char * program_name;

void die(char * error){
    fprintf(stderr, "%s: %s", program_name, error);
    printf("bench help menu:\s\t%s [test]"
           "available tests:"
           "\tsinglethread\s\tmultithread\s\tmutex\s",
           program_name);
   
    exit(1);
}

int main( int argc, char **argv )
{
    program_name = argv[0];

    if ( argc < 2 ){
        die("tests were not provided!");
    }
    
    return 0;
}
