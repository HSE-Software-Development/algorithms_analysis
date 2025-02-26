#!/bin/bash

pwd="$(pwd | rev | cut -d '/' -f 1 | rev)"
echo ${pwd}
if [ "${pwd}" = "algorithms_analysis" ]; then
    cd examples
    mkdir build 2> /dev/null
    cd build
    cmake ..
    make -j 2> /dev/null
    ./*_example
else
    echo "Please change directory to .../algorithms_analysis"
fi

# Usage: sh scripts/build_algo_analysis.sh