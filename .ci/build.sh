#!/bin/bash

GIT_HEAD=$(git rev-parse --verify HEAD)

echo -e "CommeCOM CI Build"
echo -e ""
echo -e "Configuration:"
echo -e "  HEAD  : ${GIT_HEAD}"
echo -e ""

set -o pipefail && rm -rf build && mkdir build && cd build && cmake -D"CMAKE_BUILD_TYPE=Release" -D"WITH_EXAMPLES=1" -D"WITH_TESTS=1" .. && make && make test
