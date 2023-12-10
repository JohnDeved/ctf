#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

typedef struct Node {
    struct Node *next;  // Offset 0x0 length 8
    char value;         // Offset 0x8 length 1
    char secret;        // Offset 0x9 length 1
    // Padding: 6 bytes (to align to 16 bytes)
} Node;

Node *append_list(Node *head, char value, char secret) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->value = value;
    new_node->secret = secret;
    new_node->next = head;
    return new_node;
}

int pos_in_list(Node *head, char value) {
    Node *current = head;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

Node *init_shuffle_list(char *buffer) {
    int fd = open("/dev/urandom", O_RDONLY);
    Node *head = NULL;
    char random_value;

    for (int i = 0; i < 0xaf; i++) {
        do {
            read(fd, &random_value, 1);
        } while (random_value >= 0xaf || pos_in_list(head, random_value));

        head = append_list(head, random_value, buffer[i]);
    }

    close(fd);
    return head;
}

void shuf(Node *head, char *buffer) {
    Node *current = head;
    while (current != NULL) {
        buffer[(unsigned char)current->value] = current->secret;
        current->secret = 0;
        current = current->next;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <secret file>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Opening file");
        return -1;
    }

    char *buffer = (char *)mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (buffer == MAP_FAILED) {
        perror("Mapping file");
        return -1;
    }

    Node *head = init_shuffle_list(buffer);
    shuf(head, buffer);
    puts(buffer);

    return 0;
}