#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_logic.h"
#include "user_input.h"

int isMoveValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    // Check if spell is in the list
    int validSpell = 0;
    for (int i = 0; i < numSpells; i++) {
        if (strcmp(spell, spells[i]) == 0) {
            validSpell = 1;
            break;
        }
    }

    // Check if spell has been repeated
    int repeatedSpell = 0;
    for (int i = 0; i < boardSize; i++) {
        if (strcmp(spell, board[i]) == 0) {
            repeatedSpell = 1;
            break;
        }
    }

    if (!validSpell) {
        printf("Invalid spell! Spell not in the list.\n");
        return 0;
    } else if (repeatedSpell) {
        printf("Invalid spell! Spell has already been cast.\n");
        return 0;
    } else {
        return 1;
    }
}

// Add a spell to the board
void addToBoard(char spell[], char board[][MAX_SPELL_LENGTH], int* boardSize) {
    strcpy(board[*boardSize], spell);
    (*boardSize)++;
}

int coinToss() {
    return rand() % 2;
}

int playGame(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize) {
    int currentPlayer = startingPlayer;
    int winner = -1; // -1 for no winner, 0 for player 1, 1 for player 2

    printf("%s starts!\n", (currentPlayer == 0) ? player1 : player2);

    while (1) {
        char spell[MAX_SPELL_LENGTH];
        getPlayerSpell(currentPlayer, spell, player1, player2);

        if (!isMoveValid(spell, spells, numSpells, board, *boardSize)) {
            // Invalid move, repeat turn
            continue;
        }

        addToBoard(spell, board, boardSize);

        // Check if the game has ended
        int validMoveExists = 0;
        for (int i = 0; i < numSpells; i++) {
            if (spell[strlen(spell) - 1] == spells[i][0]) {
                if (!isMoveValid(spells[i], spells, numSpells, board, *boardSize)) {
                    continue;
                }
                validMoveExists = 1;
                break;
            }
        }

        if (!validMoveExists) {
            winner = currentPlayer;
            break;
        }

        // Next player
        currentPlayer = 1 - currentPlayer;
    }

    return winner;
}
