// Eric Oliver
// COSC 3355.001 - Operating Systems
// Date of Submission 1/29/2025

#include <stdio.h>

int main(int argc, char *argv[]) {
    int max_input = 1024; // Create max_input length variable
    char input[max_input]; // Create char array to hold the user's input
    int word_count;    // Create int variable to count words
    int part_of_word;  // Create int variable to track if a character is part of a word

    while (1) {  // Infinite loop to keep asking for input until valid input is received
        word_count = 0;  // Reset word count
        part_of_word = 0; // Reset word tracking variable

        printf("Enter a series of space-separated words up to 1024 characters:\n"); // Prompt user to input words
  
        if (fgets(input, max_input, stdin) == NULL) { // Use fgets() to read input 
            printf("Please enter a correct input.\n"); 
            continue; // Restarts the loop instead of exiting
        }

        if (input[0] == '\n') { // Checking for empty input (new line)
            printf("Input is empty. Please enter some words.\n");
            continue;
        }
  
        for (int i = 0; input[i] != '\0'; i++) { // Iterate through the input character by character
            if (input[i] == ' ') { // Check if the character is a space
                if (part_of_word) { // If currently inside a word
                    word_count++;   // Count the word
                    part_of_word = 0; // Reset tracking variable
                }
            } else if (input[i] != '\n') { // Exclude the newline character from being part of a word
                part_of_word = 1; // Mark that we are in a word
            }
        }

        if (part_of_word) { // Handle the last word in the input
            word_count++;   
        }

        printf("Number of words entered: %d\n", word_count); // Output the word count

        break; // Exit loop after a valid input is processed
    }

    return 0;
}


// compile code
//gcc ––std=c11 –Wall –Werror wordcount.c –o wordcount

// run code
// ./word_count
