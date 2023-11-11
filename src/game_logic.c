#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_logic.h"
#include "user_input.h"



// Function: isMoveValid
// Signature: int isMoveValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize)
// Requirement: Checks if a given spell is valid (in spell list and not repeated).
// Effects: Returns 1 if valid; otherwise prints error message and returns 0.
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

// Function: addToBoard
// Signature: void addToBoard(char spell[], char board[][MAX_SPELL_LENGTH], int* boardSize)
// Requirement: Adds a spell to the game board.
// Effects: Copies 'spell' into the board and increments 'boardSize'.
void addToBoard(char spell[], char board[][MAX_SPELL_LENGTH], int* boardSize) {
    strcpy(board[*boardSize], spell);
    (*boardSize)++;
}



// Function: coinToss
// Signature: int coinToss()
// Requirement: Generates a random outcome to simulate a coin toss.
// Effects: Returns 0 or 1, randomly decided.
int coinToss() {
    return rand() % 2;
}


// Function: playGame
// Signature: int playGame(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize)
// Requirement: Manages gameplay, alternating turns and checking for game end conditions.
// Effects: Executes game logic and determines the winner. Returns winner identifier.
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
