# bench

simple utility for cpu benchmarking

## intro

This is a benchmarking tool constructed for benchmarking CPU and memory-bound tests in the C programming language. It provides
the user insight on performance for their processor, but also the ability to construct their own tests for their own purposes.

Since we are testing for performance, we isolate test cases into many functions for uninterruptable benchmarking. 
Variable declarations, memory allocations, etc. all occur before actually starting `clock()`.

Note that the time that you will see outputted varies for each runtime. Since the tests are CPU-bound, 
the presence of background processes that utilize system resources will affect performance. Calculations are based on 
IOPS (integer operations per second), but outputted results are in milliseconds.

## build

To use bench:

    $ make
    $ ./bench
    $ ./bench [test]
    
    available tests:
     - singlethread
     - multithread

## license

[mit](https://codemuch.tech/license.txt)
