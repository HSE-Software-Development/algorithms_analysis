#!/bin/bash

# sh scripts/format_source_code.sh 
rm -r .build 2> /dev/null
mkdir .build
pushd .build
cmake ..
make -j
popd

# Usage: sh scripts/build.sh && ./.build/HSE_SD
