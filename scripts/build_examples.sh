#!/bin/bash

pwd="$(pwd | rev | cut -d '/' -f 1 | rev)"
if [ "${pwd}" = "algorithms_analysis" ]; then
    cd examples
    mkdir build 2> /dev/null
    cd build
    cmake ..
    make -j 2> /dev/null
else
    echo "Please cd to algorithms_analysis directory"
fi

# Usage: sh scripts/build_algo_analysis.sh