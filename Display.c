
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100 

#define MAX_SPELLS 100

void displaySpells(char spells[MAX_SPELLS][MAX_NAME_LENGTH], int spellCount) {
    printf("Available Spells:\n");
    for (int i = 0; i < spellCount; i++) {
        printf("%s\t", spells[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

