#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_logic.h"

int toss_coin() {
    return rand() % 2; 
}
// Validation function
int getPlayerMove(const char** spells, int numSpells, const char* previousSpell, char* playerName) {
    char spellChoice[100];

    while (1) {
        printf("%s, enter your spell choice: ", playerName);
        scanf("%s", spellChoice);

        int valid = 0;
        for (int i = 0; i < numSpells; i++) {
            if (strcmp(spellChoice, spells[i]) == 0) {
                if (strcmp(spellChoice, previousSpell) != 0) {
                    if (spellChoice[0] == previousSpell[strlen(previousSpell) - 1]) {
                        valid = 1;
                        break;
                    } else {
                        printf("Invalid move: The first character of your spell does not match the last character of the previous spell.\n");
                    }
                } else {
                    printf("Invalid move: You've already cast this spell in a previous round.\n");
                }
            }
        }

        if (valid) {
            return 1;
        } else {
            printf("Invalid move: Please choose a valid spell from the list.\n");
        }
    }
}