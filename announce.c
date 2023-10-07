
#include <stdio.h>
#include <string.h>

#define MAX_SPELLS 100
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int used;  // 0 for unused, 1 for used
} Spell;

int checkValidSpell(Spell spells[MAX_SPELLS], char chosenSpell[MAX_NAME_LENGTH], char lastSpell[MAX_NAME_LENGTH]) {
    char lastChar = lastSpell[strlen(lastSpell) - 1];

    for (int i = 0; i < MAX_SPELLS; i++) {
        if (spells[i].used == 0 && strcmp(spells[i].name, chosenSpell) == 0 && chosenSpell[0] == lastChar) {
            spells[i].used = 1;
            return 1;  // Valid spell
        }
    }
    return 0;  // Invalid spell
}

void announceWinner(int player) {
    printf("Player %d wins!\n", player);
}
