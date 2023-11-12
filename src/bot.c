#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bot.h"
#include "game_logic.h"
#include "user_input.h"

static int botDifficulty;

// Initializes the bot with a given difficulty level.
// Parameters:
// difficulty: An integer value representing the bot's difficulty level.
// Effects:
// Sets the global variable botDifficulty to the provided difficulty value.
void initializeBot(int difficulty) {
    botDifficulty = difficulty;
}

// Chooses a move for the bot on easy difficulty.
// Parameters:
// spells: A 2D array of characters representing the list of available spells.
// numSpells: An integer indicating the number of spells.
// board: A 2D array of characters representing the game board.
// boardSize: An integer representing the number of spells on the board.
// Effects:
// Returns the index of the selected spell for an easy bot move, or -1 if no valid move is found.
int chooseBotMoveEasy(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    if (boardSize == 0) {
        // Bot starts first, no need to check for valid spells
        int botMoveIndex = rand() % numSpells; // Choose any spell randomly
        return botMoveIndex;
    }
    for (int i = 0; i < numSpells; i++) {
        if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            if (isMoveValidBot(spells[i], spells, numSpells, board, boardSize)) {
                return i;   // Bot chooses the first valid spell it finds
            }
        }
    }

    return -1; // Bot couldn't find a valid spell
}


// Chooses a move for the bot on medium difficulty, prioritizing moves that limit the opponent's options.
// Parameters and effects similar to chooseBotMoveEasy.
// Prioritize spells that limit the opponent's options in the next turn.
int chooseBotMoveMedium(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    int bestMoveIndex = -1;
    int bestOpponentOptions = numSpells + 1; // Initialize with a value greater than the maximum possible options

    char tempBoard[MAX_SPELLS][MAX_SPELL_LENGTH];
    int tempBoardSize = boardSize;

    for (int i = 0; i < numSpells; i++) {
        // Check if the spell is valid and has not been used before
        if (boardSize == 0) {
            if (isMoveValidBot(spells[i], spells, numSpells, board, boardSize)) {
                // Simulate choosing the current spell to see how it limits the opponent's options
                memcpy(tempBoard, board, sizeof(tempBoard));
                addToBoard(spells[i], tempBoard, &tempBoardSize);

                int opponentOptions = 0;
                for (int j = 0; j < numSpells; j++) {
                    if (spells[j][0] == tempBoard[tempBoardSize - 1][strlen(tempBoard[tempBoardSize - 1]) - 1])
                        if (isMoveValidBot(spells[j], spells, numSpells, tempBoard, tempBoardSize)) {
                            opponentOptions++;
                        }
                }
                // If this move limits the opponent's options more than the current best move,
                // update the best move index
                if (opponentOptions < bestOpponentOptions) {
                    bestOpponentOptions = opponentOptions;
                    bestMoveIndex = i;
                }
            }
        } else if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            if (isMoveValidBot(spells[i], spells, numSpells, board, boardSize)) {
                // Simulate choosing the current spell to see how it limits the opponent's options
                memcpy(tempBoard, board, sizeof(tempBoard));
                addToBoard(spells[i], tempBoard, &tempBoardSize);

                int opponentOptions = 0;
                for (int j = 0; j < numSpells; j++) {
                    if (spells[j][0] == tempBoard[tempBoardSize - 1][strlen(tempBoard[tempBoardSize - 1]) - 1])
                        if (isMoveValidBot(spells[j], spells, numSpells, tempBoard, tempBoardSize)) {
                            opponentOptions++;
                        }
                }
                // If this move limits the opponent's options more than the current best move,
                // update the best move index
                if (opponentOptions < bestOpponentOptions) {
                    bestOpponentOptions = opponentOptions;
                    bestMoveIndex = i;
                }
            }
        }
    }
    return bestMoveIndex;
}


// Chooses a move for the bot on hard difficulty. It checks for winning and blocking moves, and defaults to the medium strategy if neither is available.
// Parameters: Same as chooseBotMoveMedium.
// Effects: Returns the index of the chosen spell.
int chooseBotMoveHard(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    int winningMoveIndex = findWinningMove(spells, numSpells, board, boardSize);

    if (winningMoveIndex != -1) {
        // Perform the winning move if available
        return winningMoveIndex;
    }

    int blockingMoveIndex = findBlockingMove(spells, numSpells, board, boardSize);

    if (blockingMoveIndex != -1) {
        // Perform a blocking move if available
        return blockingMoveIndex;
    }

    // If no winning or blocking moves, use the medium difficulty strategy
    return chooseBotMoveMedium(spells, numSpells, board, boardSize);
}


// Finds a winning move for the bot.
// Parameters: Same as chooseBotMoveMedium.
// Effects: Returns the index of a winning move if one exists, otherwise returns -1.
int findWinningMove(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    // Check if there is a move that leads to victory
    for (int i = 0; i < numSpells; i++) {
        if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            if (isMoveValidBot(spells[i], spells, numSpells, board, boardSize)) {
                // Simulate choosing the current spell to see if it leads to victory
                addToBoard(spells[i], board, &boardSize);

                if (boardSize == numSpells) {
                    // This move leads to victory
                    removeLastSpell(board, &boardSize); // Undo the simulated move
                    return i;
                }

                // Undo the simulated move
                removeLastSpell(board, &boardSize);
            }
        }
    }

    return -1; // No winning move found
}


// Finds a blocking move for the bot.
// Parameters: Same as chooseBotMoveMedium.
// Effects: Returns the index of a blocking move if one exists, otherwise returns -1.
int findBlockingMove(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
    // Check if there is a move that blocks the opponent from winning
    for (int i = 0; i < numSpells; i++) {
        if (spells[i][0] == board[boardSize - 1][strlen(board[boardSize - 1]) - 1]) {
            if (isMoveValidBot(spells[i], spells, numSpells, board, boardSize)) {
                // Simulate the opponent choosing the current spell to see if it leads to victory for them
                addToBoard(spells[i], board, &boardSize);

                int opponentWinningMove = findWinningMove(spells, numSpells, board, boardSize);

                // Undo the simulated moves
                removeLastSpell(board, &boardSize);

                if (opponentWinningMove != -1) {
                    // This move blocks the opponent from winning
                    return i;
                }
            }
        }
    }

    return -1; // No blocking move found
}

// Manages a game session between a human player and the bot.
// Parameters:
// player1, player2: Character arrays representing the player names.
// startingPlayer: Integer indicating the starting player.
// spells, numSpells, board, boardSize: Same as in the previous functions.
// Effects:
// Controls game turns, validates moves, and determines the winner. Returns the index of the winning player, or -1 if no winner.
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
            int botMoveIndex = -1;

            if (botDifficulty == 1) {
                botMoveIndex = chooseBotMoveEasy(spells, numSpells, board, *boardSize);
            } else if (botDifficulty == 2) {
                botMoveIndex = chooseBotMoveMedium(spells, numSpells, board, *boardSize);
            } else if (botDifficulty == 3){
                botMoveIndex = chooseBotMoveHard(spells, numSpells, board, *boardSize);
            }

            if (botMoveIndex != -1) {
                strcpy(spell, spells[botMoveIndex]);
                printf("(%s) plays: %s\n", player2, spell);
            } else {
                printf("(%s) has no valid moves.\n", player2);
                winner = 1;
                break;
            }
        }

        if (!isMoveValidBot(spell, spells, numSpells, board, *boardSize)) {
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