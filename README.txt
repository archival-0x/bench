====
bench
====


1. Introduction

Testing for perfomance of specific programmatic tasks is important, especially when
constructing high-latency systems. This is a benchmarking tool constructed for
benchmarking CPU and memory-bound tests in the C programming language. It provides
the user insight on performance for their processor, but also the ability to construct
their own tests for their own purposes.

Since we are testing for performance, we isolate test cases into many functions
for uninterruptable benchmarking. Variable declarations, memory allocations, etc.
all occur before actually starting clock().

Note that the time that you will see outputted varies for each runtime. Since
the tests are CPU-bound, the presence of background processes that utilize system
resources will affect performance.

2. Benchmark Tests

Calculations are based on IOPS (integer operations per second), but outputted
results are in milliseconds.

* IOPS CPU-bound stack-based buffer write (single and multi-threaded)

    Description:
      Utilizing a writable buffer for benchmarking. Flexible for
      single and multi-threaded support. Configurable constants
      are ITERATIONS and BUFFER_SIZE.

    Execution Process:
     * 1. Create a cycle
     * 2. For each element of the array, set to arbitrary value
     * 3. Re-run, NULL each element
     * 4. Finish benchmark, output IOPS result

3. Installation and Build

To use bench:

    make
    ./bench
    ./bench [test]
    available tests:
     - singlethread
     - multithread

4. Contributions

Please submit and issue or pull request for new features, tests, fixes, etc.
