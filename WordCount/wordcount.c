// Eric Oliver
// COSC 3355.001 - Operating Systems
// Programming Assignment #1 - WordCount
// Date of Submission: 1/29/2025

#include <stdio.h>

int main(int argc, char *argv[]) {
    int max_input = 1024; // Create var for maximum input length
    char input[max_input]; // Create char array for user input
    int word_count;    // Create word counting variable
    int part_of_word;  // Create tracking variable to track if we are inside a word

    while (1) {  // Infinite loop until valid input is received
        word_count = 0;  // Reset word counting variable
        part_of_word = 0; // Reset tracking variable

        printf("Enter a series of space-separated words up to 1024 characters:\n");

        if (fgets(input, max_input, stdin) == NULL) { // Read input with fgets
            printf("Please enter a valid input, a series of space-separated words up to 1024 characters:.\n");
            continue; // Restart loop if not a valid input
        }

        int only_spaces = 1; // Set only_spaces to True - This is to check if input is only spaces or empty
        int last_non_space_index = -1; // Track the last non-space character

        for (int i = 0; input[i] != '\0' && input[i] != '\n'; i++) { // Iterate through array checking for null terminator or newline character
            if (input[i] != ' ') { // If any non-space character is found
                only_spaces = 0; // Set only_spaces to False
                last_non_space_index = i; // Update last non-space character position
            }
        }

        if (only_spaces) { // If input is only spaces or empty, prompt user to try again
            printf("Input is empty or contains only spaces. Please enter series of space-separated words up to 1024 characters:.\n");
            continue;
        }

        for (int i = 0; i <= last_non_space_index; i++) { // Iterate through input and stop at the last non-space character
            if (input[i] == ' ') { // If the character is a space
                if (part_of_word) { // If we are inside a word
                    word_count++;   // Count the word
                    part_of_word = 0; // Reset tracking variable
                }
            } else { // It's a valid character (not a space)
                part_of_word = 1; // We are inside a word
            }
        }

        if (part_of_word) { // If the last sequence of chars is a word, count it
            word_count++;   
        }

        printf("Number of words entered: %d\n", word_count);

        break; // Exit after processing a valid input
    }

    return 0;
}

