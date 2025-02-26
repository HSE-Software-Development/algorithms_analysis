#!/bin/bash

pwd="$(pwd | rev | cut -d '/' -f 1 | rev)"
echo ${pwd}
if [ "${pwd}" = "algorithms_analysis" ]; then
    cd cpp
    mkdir build 2> /dev/null
    cd build
    cmake ..
    make -j

    if [ -z "$1" ]; then
        ./tests/algo_analysis_tests
    else
        if [ $1 -gt 0 ]; then
            ./tests/algo_analysis_tests
        fi
    fi
else
    echo "Please change directory to .../algorithms_analysis"
fi

# Usage: sh scripts/build_algo_analysis.sh