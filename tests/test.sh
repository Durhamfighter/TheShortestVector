#!/bin/bash

# Specify the location of the files
file_location="generates"


if [ -d "$file_location" ]; then
    # Iterate over each .svp file found
    for file in "$file_location"/*.txt; do
        echo "Evaluating: $file"

        # Execute the command

        ../runme $(cat "$file")
        
        # Read the result from result.txt
        if [ -f result.txt ]; then
            result=$(cat result.txt)

            # Fetch the expected result from the .svs file
            echo "Result: $result"
        else
            echo "result.txt was not generated for $file"
        fi
    done
else
    echo "No .txt files found in $file_location."
fi