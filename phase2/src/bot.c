#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bot.h"
#include "game_logic.h"
#include "user_input.h"

static int botDifficulty;

void initializeBot(int difficulty) {
    botDifficulty = difficulty;
}

int chooseBotMove(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    for (int i = 0; i < numSpells; i++) {
        if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            return i; // Bot chooses the first valid spell it finds
        }
    }

    return -1; // Bot couldn't find a valid spell
}

int playAgainstBot(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH],
                   int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize) {
    int currentPlayer = startingPlayer;
    int winner = -1; // Default value for no winner

    printf("(%s) starts!\n", (currentPlayer == 0) ? player1 : player2);

    char lastSpell[MAX_SPELL_LENGTH] = ""; // Previous spell played

    while (1) {
        char spell[MAX_SPELL_LENGTH];

        if (currentPlayer == 0) {
            getPlayerSpell(currentPlayer, spell, player1, player2);
        } else {
            if (*boardSize == 0) {
                // Bot starts first, no need to check for valid spells
                int botMoveIndex = rand() % numSpells; // Choose any spell randomly
                strcpy(spell, spells[botMoveIndex]);
                printf("(%s) plays: %s\n", player2, spell);
            } else {
                int botMoveIndex = chooseBotMove(spells, numSpells, board, *boardSize);

                if (botMoveIndex != -1) {
                    strcpy(spell, spells[botMoveIndex]);
                    printf("(%s) plays: %s\n", player2, spell);
                } else {
                    printf("(%s) has no valid moves.\n", player2);
                    winner = 1;
                    break;
                }
            }
        }

        if (!isMoveValid(spell, spells, numSpells, board, *boardSize)) {
            winner = 1 - currentPlayer;
            break;
        }

        if (lastSpell[0] != '\0' && spell[0] != lastSpell[strlen(lastSpell) - 1]) {
            printf("Invalid spell Wizard! The first character does not match the last character of the previous spell.\n");
            winner = 1 - currentPlayer;
            break;
        }

        addToBoard(spell, board, boardSize);

        if (*boardSize == numSpells) {
            winner = -1;
            break;
        }

        strcpy(lastSpell, spell);

        currentPlayer = 1 - currentPlayer;

        int opponentHasValidSpells = 0;
        for (int i = 0; i < numSpells; i++) {
            if (spells[i][0] == lastSpell[strlen(lastSpell) - 1]) {
                opponentHasValidSpells = 1;
                break;
            }
        }

        if (!opponentHasValidSpells) {
            winner = 1 - currentPlayer;
            printf("No more spells in the list that satisfy the character matching condition.\n");
            break;
        }
    }

    return winner;
}