#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

unsigned char talis[] = {
    0x08, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x13, 
    0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1b, 
    0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Function to clear the terminal screen
void cls(void) {
    // Print escape sequences to clear the screen and move the cursor to the top-left
    printf("\x1b[2J");
    printf("\x1b[%d;%dH",0,0);
}

// Function to read the flag from a file
void read_flag(void) {
    char local_15;
    int local_14;

    // Open the flag file
    local_14 = open("./flag.txt",0);
    if (local_14 < 0) {
        perror("\nError opening flag.txt, please contact an Administrator.\n");
        exit(1);
    }

    // Read the file character by character and print to stdout
    while(read(local_14,&local_15,1) > 0) {
        fputc((int)local_15,stdout);
    }

    // Close the file
    close(local_14);
}

// Function to set up the program
void setup(void) {
    // Set stdin and stdout to unbuffered
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);

    // Set an alarm for 127 seconds
    alarm(0x7f);
}

// Main function
int main(void) {
    int local_14;

    // Set up the program and print the banner
    setup();

    // Ask the user if they want to enchant the talisman
    printf("\nThis Great Old Talisman will protect you from the evil powers of zombies!\n\nDo you want  to enchant it with a powerful spell? (1 -> Yes, 0 -> No)\n\n>> ");
    scanf("%d", &local_14); // exploit is to manipulate local_14 to patch the exit function to call "read_flag" instead

    // Read the spell into the talisman
    printf("\nSpell: ");
    read(0,talis + local_14 * 8,2);

    // Exit the program
    exit(0x520);
}