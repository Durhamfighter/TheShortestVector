# #!/bin/bash
file_location="intrel"
bits_lengths="8 16 32"
# output_csv="8.csv"
# counter=0
# # Generate lattice vectors
# for dimension in {1..30} # Dimensions from 1 to 30
# do
#   for bit_length in $bits_lengths
#   do
#     output_file="test_${dimension}_${bit_length}.txt"
#     latticegen -randseed $counter u $dimension $bit_length | tr '\n' ' ' | sed 's/\[\(.*\)\]/\1/' > "$file_location/$output_file"
#     echo "Generated lattice vectors for dimension $dimension with $bit_length bits, saved to $file_location/$output_file"
#     ((counter++))
#   done
# done

# # Benchmarking with Hyperfine
# for file in "$file_location"/*_8.txt; do
#     echo "Evaluating: $file"

#     # Read the content of the file
#     file_content=$(cat "$file")

#     # Execute the Hyperfine command with the content of the file
#     hyperfine -N --warmup 20 "../runme $file_content" --export-csv temp.csv
#     if [ -s "$output_csv" ]; then
#         tail -n +2 temp.csv >> "$output_csv"
#     else
#         cat temp.csv > "$output_csv"
#     fi
# done

# rm temp.csv


# for file in "$file_location"/*_16.txt; do
#     echo "Evaluating: $file"

#     # Read the content of the file
#     file_content=$(cat "$file")

#     # Execute the Hyperfine command with the content of the file
#     hyperfine -N --warmup 20 "../runme $file_content" --export-csv temp.csv
#     if [ -s "16.csv" ]; then
#         tail -n +2 temp.csv >> "16.csv"
#     else
#         cat temp.csv > "16.csv"
#     fi
# done

# rm temp.csv

for file in "$file_location"/*_32_intrel.svp; do
    echo "Evaluating: $file"

    # Read the content of the file
    file_content=$(cat "$file")

    # Execute the Hyperfine command with the content of the file
    hyperfine -N --warmup 20 "../runme $file_content" --export-csv temp.csv
    if [ -s "32_intrel_after.csv" ]; then
        tail -n +2 temp.csv >> "32_intrel_after.csv"
    else
        cat temp.csv > "32_intrel_after.csv"
    fi
done

rm temp.csv