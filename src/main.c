#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"
#include "user_input.h"
#include "winner_determination.h"

int main() {
    // Initialize the game

    int numSpells;
    char** spells = readSpellsFromFile("spells.txt", &numSpells);

    char player1[50]; 
    char player2[50];

    printf("Enter Player 1's name (no spaces): ");
    scanf("%s", player1);
    printf("Enter Player 2's name (no spaces): ");
    scanf("%s", player2);

    int currentPlayer = 1; // Player 1 starts
    char* previousSpell = NULL;

    while (1) {
        // Alternate between players
        char* currentPlayerName = (currentPlayer == 1) ? player1 : player2;

        displaySpells(spells, numSpells);

        // Check validity
        int validMove = getPlayerMove(spells, numSpells, previousSpell, currentPlayerName);

        if (validMove) {

            previousSpell = strdup(spellChoice);

            if (checkWinCondition(spells, numSpells, previousSpell)) {
                printf("%s wins!\n", currentPlayerName);
                break;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }

    return 0;
}