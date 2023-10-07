#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"

static int countLinesInFile(FILE* file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);
    return count;
}

char** readSpellsFromFile(const char* filename, int* numSpells) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    *numSpells = countLinesInFile(file);

    char** spells = (char**)malloc(*numSpells * sizeof(char*));
    if (spells == NULL) {
        perror("Memory allocation error");
        exit(1);
    }

    // Read spells from the file into the array
    for (int i = 0; i < *numSpells; i++) {
        char line[100];
        if (fgets(line, sizeof(line), file) != NULL) {
            size_t len = strlen(line);
            if (line[len - 1] == '\n') {
                line[len - 1] = '\0';
            }

            // Memory Allocation
            spells[i] = strdup(line);
            if (spells[i] == NULL) {
                perror("Memory allocation error");
                exit(1);
            }
        }
    }

    fclose(file);
    return spells;
}