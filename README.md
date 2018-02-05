# bench

A performance benchmark tool for your processor

# Introduction

I wanted to test the performance of my CPU by performing computationally-taxing and iterative operations as test units. Since C is fast and does not have that much of an overhead, I wrote a benchmark tool.

# Tests

Several test units will be used to calculate performance:

* Single-threaded IOPS
* Multi-threaded IOPS
* Multi-threaded IOPS with mutex locking
