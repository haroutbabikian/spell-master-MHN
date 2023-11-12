#include <stdio.h>
#include <string.h>
#include "file_operations.h"

// Reads spells from a file and stores them in an array.
// Parameters:
// filename: A constant character pointer to the name of the file to be read.
// spells: A 2D array of characters where the spells will be stored.
// Returns:
// The number of spells read from the file. Returns 0 if there is an error opening the file.
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

// Displays the list of spells in a formatted manner.
// Parameters:
// spells: A 2D array of characters representing the list of spells.
// numSpells: An integer representing the number of spells in the array.
// Effects:
// Prints each spell in the array to the console. Spells are formatted in a tabular form, with a maximum of 5 spells per line.
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
