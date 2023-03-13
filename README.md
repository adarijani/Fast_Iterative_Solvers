# Programming Exercises for Fast Iterative Solvers

This repository contains programming exercises corresponding to the lectures "Fast Iterative Solvers" held by [Prof. May](https://www.aices.rwth-aachen.de/en/people/may) at RWTH Aachen University. The corresponding assignments can be found in the following article:

    [1] http://davidstutz.de/programming-exercises-for-mathematical-image-processing/

The assignments have been completed together with [Tobias Pohlen](http://geekstack.net/).

The examples have been tested using MatLab 2014b on Ubuntu 12.04 with OpenCV 2.4.

## Building

The C++ examples are built using CMake and based on OpenCV:

    cd mathematical-image-processing
    cd filters
    mkdir build
    cd build
    cmake ..
    make
    ./filters_cli ../lenaTest3.jpg


