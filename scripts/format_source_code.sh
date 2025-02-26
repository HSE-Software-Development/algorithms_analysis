#!/bin/bash

files="$(find . -regex ".*/*\.[c|h]pp" 2> /dev/null)"

if [ -z "$1" ]
then
    echo ""
else 
    if [ $1 -gt 0 ]; then
        echo "Found files to format: ${files}" 
    fi
fi

echo ${files} | xargs clang-format -style=file -i 2>/dev/null

# Usage: sh scripts/format_source_code.sh
