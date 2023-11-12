#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_input.h"
#include "bot.h"


// Gets the names of the players.
// Parameters:
// player1: A character array to store the name of Player 1.
// player2: A character array to store the name of Player 2 or "Bot".
// Returns:
// An integer representing the choice of opponent (1 for another player, 2 for bot).
// Effects:
// Player names are read from input. Ensures unique, single-word names with no spaces.
// Repeats prompt until valid names are entered.
int getPlayerNames(char player1[], char player2[]) {
    int choice;
    while (1) {
        printf("Enter the name of Player 1 (single word, no spaces): ");
        scanf("%s", player1);

        printf("Choose opponent:\n1. Another Player\n2. Bot\n(Enter 1 or 2)\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter the name of Player 2 (single word, no spaces): ");
            scanf("%s", player2);

            if (strcmp(player1, player2) == 0) {
                printf("Names cannot be the same. Try different names.\n");
            } else if (strchr(player1, ' ') || strchr(player2, ' ')) {
                printf("Names must be single words with no spaces. Try again.\n");
            } else {
                break;
            }
        } else if (choice == 2) {
            strcpy(player2, "Bot");
            break;
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    return choice;
}


// Prompts the current player to enter a spell.
// Parameters:
// currentPlayer: An integer indicating the current player (0 for player 1, 1 for player 2 or bot).
// spell: A character array to store the entered spell.
// player1, player2: Character arrays containing the names of the players.
// Effects:
// Prompts the current player to enter their spell choice and stores it in the 'spell' array.
void getPlayerSpell(int currentPlayer, char spell[], char player1[], char player2[]) {
    printf("%s, enter your spell choice: ", (currentPlayer == 0) ? player1 : player2);
    scanf("%s", spell);
}