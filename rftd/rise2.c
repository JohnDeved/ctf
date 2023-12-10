#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// Node structure for the linked list
typedef struct Node {
    struct Node* next;  // Pointer to the next node in the list
    char value;         // Value of the node
    char secret;        // Secret value of the node
} Node;

// Function to append a new node to the end of the list
void append_list(Node** head, char value, char secret) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for a new node
    newNode->next = NULL;  // Initialize the next pointer to NULL
    newNode->value = value;  // Set the value of the node
    newNode->secret = secret;  // Set the secret value of the node

    // If the list is empty, make the new node the head of the list
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Otherwise, traverse the list to find the last node
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        // Append the new node to the end of the list
        current->next = newNode;
    }
}

// Function to check if a value exists in the list
int pos_in_list(Node* head, char value) {
    Node* current = head;  // Start at the head of the list
    // Traverse the list
    while (current != NULL) {
        // If the current node's value matches the search value, return 1 (true)
        if (current->value == value) {
            return 1;
        }
        // Move to the next node
        current = current->next;
    }
    // If the end of the list is reached without finding the value, return 0 (false)
    return 0;
}

// Function to shuffle the list based on the values in the list
void shuf(Node* head, char* buffer) {
    Node* current = head;  // Start at the head of the list
    // Traverse the list
    while (current != NULL) {
        // Use the node's value as an index into the buffer, and set the corresponding buffer element to the node's secret value
        buffer[(unsigned char)current->value] = current->secret;
        // Reset the node's secret value to 0
        current->secret = 0;
        // Move to the next node
        current = current->next;
    }
}

// Function to initialize the shuffle list
Node* init_shuffle_list(char* buffer) {
    // Open the /dev/urandom file to get random values
    int fd = open("/dev/urandom", O_RDONLY);
    Node* head = NULL;  // Initialize the head of the list to NULL
    char* end = buffer + 0xaf;  // Set the end of the buffer

    // While there are still elements in the buffer
    while (buffer < end) {
        unsigned char randomValue;
        // Read a random value from /dev/urandom
        read(fd, &randomValue, 1);

        // While the random value is not valid (either it's too large or it already exists in the list), get a new random value
        while (randomValue >= 0xaf || pos_in_list(head, randomValue)) {
            read(fd, &randomValue, 1);
        }

        // Append a new node to the list with the random value and the current buffer value
        append_list(&head, randomValue, *buffer);
        // Move to the next element in the buffer
        buffer++;
    }

    // Close the /dev/urandom file
    close(fd);
    // Return the head of the list
    return head;
}

int main(int argc, char** argv) {
    // If no arguments are provided, print usage information and exit with an error
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <secret file>\n", argv[0]);
        return -1;
    }

    // Open the file provided as an argument
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        // If the file could not be opened, print an error message and exit with an error
        perror("Opening file");
        return -1;
    }

    // Map the file into memory
    char* buffer = (char*)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (buffer == MAP_FAILED) {
        // If the file could not be mapped, print an error message and exit with an error
        perror("Mapping file");
        return -1;
    }

    // Initialize the shuffle list with the contents of the file
    Node* head = init_shuffle_list(buffer);
    // Shuffle the list
    shuf(head, buffer);
    // Print the shuffled list
    puts(buffer);

    // Exit with success
    return 0;
}