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

int chooseBotMoveEasy(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    for (int i = 0; i < numSpells; i++) {
        if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            return i; // Bot chooses the first valid spell it finds
        }
    }

    return -1; // Bot couldn't find a valid spell
}

int calculateMatchScore(char spell1[], char spell2[]) {
    // Calculate a score indicating how well the last letter of spell1 matches the first letter of spell2
    int score = 0;
    int len1 = strlen(spell1);
    int len2 = strlen(spell2);

    for (int i = 1; i <= len1 && i <= len2; i++) {
        if (spell1[len1 - i] == spell2[i - 1]) {
            score++;
        } else {
            break; // Stop counting when a mismatch is found
        }
    }

    return score;
}

int chooseBotMoveMedium(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    int bestScore = -1;
    int bestMoveIndex = -1;

    for (int i = 0; i < numSpells; i++) {
        int validMove = 1;

        if (boardSize > 0) {
            // Check if the last letter of the chosen spell matches the first letter of any other spell on the board
            for (int j = 0; j < boardSize; j++) {
                int matchScore = calculateMatchScore(board[j], spells[i]);

                if (matchScore > 0) {
                    validMove = 0;
                    break;
                }
            }
        }

        if (validMove) {
            // Calculate a score indicating how well the last letter of the chosen spell matches the first letter of other spells
            int totalMatchScore = 0;

            for (int j = 0; j < numSpells; j++) {
                if (i != j) {
                    totalMatchScore += calculateMatchScore(spells[i], spells[j]);
                }
            }

            // Update the best move if the current move has a higher total match score
            if (totalMatchScore > bestScore) {
                bestScore = totalMatchScore;
                bestMoveIndex = i;
            }
        }
    }

    return bestMoveIndex;
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
                int botMoveIndex = -1;

                if (botDifficulty == 1) {
                    int botMoveIndex = chooseBotMoveEasy(spells, numSpells, board, *boardSize);
                } else if (botDifficulty == 2) {
                    int botMoveIndex = chooseBotMoveMedium(spells, numSpells, board, *boardSize);
                }// } else if (botDifficulty == 3){
                //     int botMoveIndex = chooseBotMoveHard(spells, numSpells, board, *boardSize);
                // }

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