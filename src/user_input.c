#include <stdio.h>
#include <string.h>
#include "file_operations.h"

int readSpells(const char* filename, char spells[][MAX_SPELL_LENGTH]) {
    //*testing strategy*
    //partitioning readSpells as follows:  valid file, empty file, file containing too many spells
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
void displaySpells(char spells[][MAX_SPELL_LENGTH], int numSpells) {
    //*testing strategy*
    //partitioning displaySpells as follows:  normal input size, small input size, maximum input size
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