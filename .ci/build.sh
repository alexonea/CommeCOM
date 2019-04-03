#!/bin/bash

mkdir build && cd build
cmake -D"CMAKE_BUILD_TYPE=Release" -D"WITH_EXAMPLES=1" -D"WITH_TESTS=1" .. && make && make test
