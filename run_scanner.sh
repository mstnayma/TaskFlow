#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <input_file.tfl>"
    exit 1
fi

INPUT_FILE=$1

if [ ! -f "$INPUT_FILE" ]; then
    echo "Error: File '$INPUT_FILE' not found!"
    exit 1
fi

# Compile the scanner
g++ -std=c++11 -o taskflow_scanner scanner.cpp

# Run the scanner on the input file
./taskflow_scanner "$INPUT_FILE"
