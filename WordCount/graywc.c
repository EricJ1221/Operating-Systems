// Eric Oliver
// COSC 3355.001 - Operating Systems
// Programming Assignment #2 - graywc.c
// Date of Submission: 2/17/2025

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void count_file(const char *filename, int *total_lines, int *total_words, int *total_bytes); // Function Prototype


void count_file(const char *filename, int *total_lines, int *total_words, int *total_bytes) { // Pointers for file name and storage variables
    int file_descriptor = open(filename, 0); // Open file for reading
    if (file_descriptor == -1) {// Sends error if no filename provided
        fprintf(stderr, "Error: Unable to open file %s\n", filename); 
        return; // Returns stdin, stdout, stderr if successful
    }

    char buffer[BUFFER_SIZE]; // Char array to hold chunks of the file
    ssize_t bytes_read; // Found "ssize_t" in the Man pages, section 2 under "read(2)":
                        // "read()"" states that "read()" returns a "ssize_t" which represents 
                        // the number of bytes read or "-1" if an error occurs. 
                        // I am using "ssize_t bytes_read" to store this value 
                        // allowing me to detect errors and end-of-file conditions properly.
    
    
    int lines = 0, words = 0, bytes = 0; // Counter variables
    int in_word = 0; // Var to track if inside or outside of a word

    while ((bytes_read = read(file_descriptor, buffer, BUFFER_SIZE)) > 0) { // Read file up to buffer size
        bytes += bytes_read;
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') { // Checks for new line
                lines++;
            }
            if (buffer[i] == ' ' || buffer[i] == '\n' || buffer[i] == '\t') { // Handles whitespace characters
                in_word = 0; // Not inside of a word
            } else if (!in_word) {
                in_word = 1; // Inside of a word
                words++;
            }
        }
    }

    if (bytes_read == -1) {
        fprintf(stderr, "Error: Failed to read file %s\n", filename); // Returns error if read fails
    }  // Found "fprintf" in the Man pages, section 3 under "fprintf(3)":  
        // "fprintf()" is part of the printf family and allows formatted output  
        // to be written to a specific file stream instead of just standard output.  
        // I initially encountered compilation errors and learned that "printf()"  
        // would not work correctly for the intended implementation.  
        // "fprintf" requires a FILE* stream as the first argument, not a filename.  
        // I am using "fprintf(stderr, ...)" to print error messages to standard error,  
        // ensuring they are separated from normal program outputs for debugging.   

    if (close(file_descriptor) == -1) {
    fprintf(stderr, "Error: Failed to close file %s\n", filename);
    }

    printf("%d %d %d %s\n", lines, words, bytes, filename); // Use printf() when printing to stdout

    *total_lines += lines; // Updating global counter vars
    *total_words += words;
    *total_bytes += bytes;
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // Checks # of command line arguments
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]); // Error msg if no args provided
        return 1;
    }

    int total_lines = 0, total_words = 0, total_bytes = 0; // Set counter variables

    for (int i = 1; i < argc; i++) {
        count_file(argv[i], &total_lines, &total_words, &total_bytes); // Call count file function to process file
    }

    if (argc > 2) { // Checks for orrect # of args,
        printf("%d %d %d total\n", total_lines, total_words, total_bytes); // output lines, words, bytes
    }

    return 0;
}
