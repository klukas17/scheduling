#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <file_name>"
    exit 1
fi

file_name="$1"

for sub_directory in "."/*/; do
    if [ -f "$sub_directory/$file_name" ]; then
        echo "Contents of $file_name in $sub_directory:"
        echo ""
        cat "$sub_directory/$file_name"
        echo ""
        echo "-------------------------------------"
    else
        echo "No $file_name found in $sub_directory"
        echo "-------------------------------------"
    fi
done
