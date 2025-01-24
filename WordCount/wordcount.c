#include <stdio.h>

#define MAX_INPUT 1024 // Max input length

int main(int argc, char *argv[]) {
    char input[MAX_INPUT]; // Char array to hold the user's input
    int word_count = 0;    // Int variable to count words
    int part_of_word = 0;  // Int variable to track if a character is part of a word

    if (argc != 1) {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }

    printf("Enter a series of space-separated words (up to 1024 characters):\n"); // Prompt user for sentence

   
    if (fgets(input, MAX_INPUT, stdin) == NULL) { // Take in user input    
        printf("Please type a series of space-separated words (up to 1024 characters):\n"); // Prompt user to add a correct input
    }
    else
        printf("Thank you for following the instructions of the previous prompt.\n");
   
    for (int i = 0; input[i] != '\0'; i++) {  // Iterate through the input character by character
        if (input[i] == ' ') { // Check if the character is a space
            if (part_of_word) {
                word_count++;      // Count the word
                part_of_word = 0;  // Reset tracking variable
            }
        } else {
            if (!part_of_word) { // Mark the start of a word if a non-whitespace char
                part_of_word = 1;
            }
        }
    }

    if (part_of_word) { // Handle the last word in the input
        word_count++;
    }

    // Output the word count
    printf("Number of words entered: %d\n", word_count);

    return 0;
}