#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"
#include "user_input.h"


// Checks if a given spell is valid.
// Parameters:
// spell: A character array representing the spell to be validated.
// spells: A 2D array of characters representing the list of available spells.
// numSpells: An integer indicating the number of spells.
// board: A 2D array of characters representing the game board.
// boardSize: An integer representing the number of spells on the board.
// Returns:
// 1 if the move is valid, 0 otherwise.
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
        printf("Invalid spell Wizard! Spell not in the list.\n");
        return 0;
    } else if (repeatedSpell) {
        printf("Invalid spell Wizard! Spell has already been cast.\n");
        return 0;
    } else {
        return 1;
    }
}


// Checks if a given spell is valid for the bot.
// Parameters: Same as isMoveValid.
// Returns:
// 1 if the move is valid, 0 otherwise. Designed for bot use, does not print messages.
int isMoveValidBot(char spell[], char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize) {
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
        return 0;
    } else if (repeatedSpell) {
        return 0;
    } else {
        return 1;
    }
}


// Adds a spell to the board.
// Parameters:
// spell: A character array representing the spell to be added.
// board: A 2D array of characters representing the game board.
// boardSize: A pointer to an integer representing the current number of spells on the board.
// Effects:
// The spell is added to the board, and boardSize is incremented.
void addToBoard(char spell[], char board[][MAX_SPELL_LENGTH], int* boardSize) {
    strcpy(board[*boardSize], spell);
    (*boardSize)++;
}

// Removes the last spell from the board.
// Parameters:
// board: A 2D array of characters representing the game board.
// boardSize: A pointer to an integer representing the current number of spells on the board.
// Effects:
// Decrements boardSize and clears the last spell from the board.
void removeLastSpell(char board[][MAX_SPELL_LENGTH], int* boardSize) {
    (*boardSize)--;
    board[*boardSize][0] = '\0';
}


// Determines the starting player with a coin toss.
// Returns:
// An integer representing the result of the coin toss (0 or 1).
int coinToss() {
    srand(time(NULL));
    return rand() % 2;
}

// Manages the gameplay between two players.
// Parameters:
// player1, player2: Character arrays representing the player names.
// startingPlayer: Integer indicating the starting player.
// spells, numSpells, board, boardSize: Similar to the other functions.
// Returns:
// The index of the winning player, -1 if no winner.
int playGame(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize) {
    int currentPlayer = startingPlayer;
    int winner = -1; // -1 for no winner, 0 for player 1, 1 for player 2

    printf("%s starts!\n", (currentPlayer == 0) ? player1 : player2);

    char lastSpell[MAX_SPELL_LENGTH] = ""; // Previos spell played

    while (1) {
        char spell[MAX_SPELL_LENGTH];
        getPlayerSpell(currentPlayer, spell, player1, player2);

        if (!isMoveValid(spell, spells, numSpells, board, *boardSize)) {
            winner = 1 - currentPlayer;
            break;
        }

        // Checks the Spell Master Condition
        if (lastSpell[0] != '\0' && spell[0] != lastSpell[strlen(lastSpell) - 1]) {
            printf("Invalid spell Wizard! The first character does not match the last character of the previous spell.\n");
            winner = 1 - currentPlayer;
            break;
        }

        addToBoard(spell, board, boardSize);

        // Check if the game has ended
        if (*boardSize == numSpells) {
            winner = -1;
            break;
        }

        // Update last spell played
        strcpy(lastSpell, spell);

        // Next player
        currentPlayer = 1 - currentPlayer;

        // Check if other player has any more options lol
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
