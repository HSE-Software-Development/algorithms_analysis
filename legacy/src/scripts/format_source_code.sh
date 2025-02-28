#!/bin/bash

find . -regex ".*/*\.[c|h]pp" 2> /dev/null | xargs clang-format -style=file -i

# Usage: sh scripts/format_source_code.sh
