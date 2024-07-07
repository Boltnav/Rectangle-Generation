#!/bin/bash

# Specify the output directory (adjust this path as necessary)
OUTPUT_DIR="textFiles"

# Create the output directory if it does not exist
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# Compile the program

# Run the program x times
for i in {1..20}; do
    g++ -o RandomGeneration RandomGeneration.cpp
    ./RandomGeneration
    # Move and rename the output file to the output directory
    mv Generated.txt "$OUTPUT_DIR/Generated_$i.txt"
done
