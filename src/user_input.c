#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_input.h"


// Function: getPlayerNames
// Signature: void getPlayerNames(char player1[], char player2[])
// Requirement: Collects names for two players, ensuring they are single words without spaces and not identical.
// Effects: Prompts for player names, validating and assigning them to player1 and player2.
void getPlayerNames(char player1[], char player2[]) {
    while (1) {
        printf("Enter the name of Player 1 (single word, no spaces): ");
        scanf("%s", player1);
        printf("Enter the name of Player 2 (single word, no spaces): ");
        scanf("%s", player2);

        if (strcmp(player1, player2) == 0) {
            printf("Names cannot be the same. Try different names.\n");
        } else if (strchr(player1, ' ') || strchr(player2, ' ')) {
            printf("Names must be single words with no spaces. Try again.\n");
        } else {
            break;
        }
    }
}

// Function: getPlayerSpell
// Signature: void getPlayerSpell(int currentPlayer, char spell[], char player1[], char player2[])
// Requirement: Prompts the current player to enter a spell choice.
// Effects: Displays a prompt for spell input and assigns the entered spell to 'spell'.
void getPlayerSpell(int currentPlayer, char spell[], char player1[], char player2[]) {
    printf("%s, enter your spell choice: ", (currentPlayer == 0) ? player1 : player2);
    scanf("%s", spell);
}