#include <stdbool.h>
#include <string.h>

// Function to compare the input string with a specific string
bool compare_string(char *input) {
    // The specific string is represented as a sequence of 8-byte integers
    uint64_t part1 = 0x743474737b425448;
    uint64_t part2 = 0x5f3562316c5f6331;
    uint64_t part3 = 0x6c3030635f747562;
    uint32_t part4 = 0x7d7233;

    // Combine the parts into a single string
    char target[29] = {0};
    memcpy(target, &part1, 8);
    memcpy(target + 8, &part2, 8);
    memcpy(target + 16, &part3, 8);
    memcpy(target + 24, &part4, 5);

    // Compare the input string with the target string
    return strcmp(input, target) == 0;
}