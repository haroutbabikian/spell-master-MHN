#include <stdio.h>
#include <stdlib.h>
#include "user_input.h"
#include "file_operations.h"
#include "game_logic.h"
#include "winner_determination.h"
#include "bot.h"

int main() {
    char player1[MAX_NAME_LENGTH];
    char player2[MAX_NAME_LENGTH];
    char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
    int numSpells;

    numSpells = readSpells("spells.txt", spells);
    
    if (numSpells == 0) {
        return 1;
    }

    int choice = getPlayerNames(player1, player2);

    if (choice == 2) {
        int difficulty;
        printf("Choose bot difficulty:\n1. Easy\n2. Medium\n3. Hard\n(Enter 1, 2 or 3)\n");
        scanf("%d", &difficulty);
        while (getchar() != '\n');
        if (difficulty < 1 || difficulty > 3) {
            printf("Invalid choice. Defaulting to easy.\n");
            difficulty = 1;
        }

        // Call a function to initialize the bot with the chosen difficulty
        initializeBot(difficulty);
    }

    int startingPlayer = coinToss();

    char board[MAX_SPELLS][MAX_SPELL_LENGTH];
    int boardSize = 0;

    displaySpells(spells, numSpells);

    int winner;
    if (choice == 1) {
        winner = playGame(player1, player2, startingPlayer, spells, numSpells, board, &boardSize);
    } else {
        winner = playAgainstBot(player1, player2, startingPlayer, spells, numSpells, board, &boardSize);
    }

    announceWinner(player1, player2, winner);

    return 0;
}