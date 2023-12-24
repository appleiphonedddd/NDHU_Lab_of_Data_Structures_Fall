#!/bin/bash

# Check if the user provided a C source file as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <source_file.c>"
    exit 1
fi

# Get the name of the source file without the extension
source_file="$1"
file_name="${source_file%.*}"

# Compile the C code to create an executable
g++ -o "$file_name" "$source_file"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executing '$file_name'..."
    
    # Execute the compiled binary
    "./$file_name"
    
    # Check if execution was successful
    if [ $? -eq 0 ]; then
        echo "Execution successful. Removing '$file_name'..."
        
        # Remove the compiled binary
        rm "$file_name"
        
        echo "'$file_name' removed."
    else
        echo "Execution failed."
    fi
else
    echo "Compilation failed."
fi
