#!/bin/bash

files="$(find . -regex ".*/*\.[c|h]pp" 2> /dev/null)"

if [ $1 -gt 0 ]; then
    echo "Found files to format: ${files}" 
fi

echo ${files} | xargs clang-format -style=file -i 2>/dev/null

# Usage: sh scripts/format_source_code.sh 0/1
