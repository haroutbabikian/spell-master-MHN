#include <stdio.h>
#include <string.h>
#include "file_operations.h"


// Function: readSpells
// Signature: int readSpells(const char* filename, char spells[][MAX_SPELL_LENGTH])
// Requirement: Reads a list of spells from a file.
// Effects: Reads spells into 'spells' array and returns the number or 0 if error.
int readSpells(const char* filename, char spells[][MAX_SPELL_LENGTH]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return 0; // Return 0 if error
    }

    int numSpells;
    fscanf(file, "%d", &numSpells);

    for (int i = 0; i < numSpells; i++) {
        fscanf(file, "%s", spells[i]);
    }

    fclose(file);
    return numSpells;
}

// Function: displaySpells
// Signature: void displaySpells(char spells[][MAX_SPELL_LENGTH], int numSpells)
// Requirement: Displays the list of spells in a formatted manner.
// Effects: Prints spells to standard output, formatted in columns.
void displaySpells(char spells[][MAX_SPELL_LENGTH], int numSpells) {
    printf("List of Spells:\n");
    for (int i = 0; i < numSpells; i++) {
        printf("%-15s", spells[i]); // Adjust the width as needed
        if ((i + 1) % 5 == 0 || i == numSpells - 1) {
            printf("\n");
        } else {
            printf("\t");
        }
    }
}