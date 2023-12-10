#include <stdio.h>

// Main function
int main(void) {
    char input[43];  // Input string
    char sum;  // Sum of two consecutive characters
    unsigned int index = 0;  // Index for the loop

    // The reference array
    unsigned char arr[] = {
        0x9c, 0x96, 0xbd, 0xaf, 0x93, 0xc3, 0x94, 0x60, 0xa2, 0xd1, 0xc2, 0xcf, 0x9c, 0xa3, 0xa6, 0x68,
        0x94, 0xc1, 0xd7, 0xac, 0x96, 0x93, 0x93, 0xd6, 0xa8, 0x9f, 0xd2, 0x94, 0xa7, 0xd6, 0x8f, 0xa0,
        0xa3, 0xa1, 0xa3, 0x56, 0x9e
    };

    // Print a prompt for the password
    puts("A voice comes from the window... 'Password?'");
    // Read the password from the user
    fgets(input, 42, stdin);

    // Loop over the characters in the password
    while (index < 37) {
        // Calculate the sum of two consecutive characters
        sum = input[index + 1] + input[index];
        // Check if the sum matches the corresponding value in the array
        if (sum != arr[index]) {
            // If the sum doesn't match, print a message and return -1
            puts("The window slams shut...");
            return -1;
        }
        // If the sum matches, increment the index
        index++;
    }

    // If all sums match, print a message and return 0
    puts("The window opens to allow you passage...");
    return 0;
}