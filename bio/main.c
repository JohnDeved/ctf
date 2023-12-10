#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

typedef int (*code)(char*);

// Function to get a handle to the dynamic library
long get_handle(void) {
    long handle;
    int memfd;
    char local_1029;
    char path[512] = {0};

    // Create a file descriptor in memory
    memfd = memfd_create(":^)", 0);
    if (memfd == -1) {
        // Exit if memfd_create failed
        exit(-1);
    }

    // Write data to the file descriptor
    for (size_t i = 0; i < 15880; i++) {
        local_1029 = __[i] ^ 0x37;
        write(memfd, &local_1029, 1);
    }

    // Create a path to the file descriptor
    sprintf(path, "/proc/self/fd/%d", memfd);
    // Open the dynamic library
    handle = (long)dlopen(path, 1);
    if (handle == 0) {
        // Exit if dlopen failed
        exit(-1);
    }

    return handle;
}

// Main function
int main(void) {
    int result;
    long handle;
    size_t newline_position;
    char input[128];
    code function;

    // Get a handle to the dynamic library
    handle = get_handle();
    // Get a pointer to the function in the dynamic library
    function = (code)dlsym((void*)handle, "DAT_00102019");
    if (function == NULL) {
        // Return -1 if dlsym failed
        return -1;
    } else {
        // Read input from the user
        fgets(input, 127, stdin);
        // Find the position of the newline character
        newline_position = strcspn(input, "\n");
        // Replace the newline character with a null character
        input[newline_position] = '\0';
        // Call the function in the dynamic library
        result = function(input);
        // Print a message based on the result of the function call
        if (result == 0) {
            puts("[x] Critical Failure");
        } else {
            puts("[*] Untangled the bundle");
        }
        // Return 0 on success
        return 0;
    }
}