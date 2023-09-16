#!/bin/bash

root_directory="."

for sub_directory in "$root_directory"/*; do
    if [ -d "$sub_directory" ]; then
        output_directory="$sub_directory/output"
        if [ -d "$output_directory" ]; then
            rm -f "$output_directory"/*
            echo "Deleted files in $output_directory"
        fi
    fi
done
