#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    char command[256];
    snprintf(command, sizeof(command), "objdump -d %s > %s", argv[1], argv[2]);
    system(command);
    if (system(command) != 0) {
        printf("Error running objdump\n");
        return 1;
    }

    printf("Disassembled code written to %s\n", argv[2]);
    return 0;
}