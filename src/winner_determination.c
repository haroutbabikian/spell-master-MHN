#include <stdio.h>
#include "winner_determination.h"


// Function: announceWinner
// Signature: void announceWinner(char player1[], char player2[], int winner)
// Requirement: Announces the winner of a game based on the 'winner' parameter.
// Effects: Prints the game result to the standard output.
void announceWinner(char player1[], char player2[], int winner) {
    if (winner == 0) {
        printf("%s wins!\n", player1);
    } else if (winner == 1) {
        printf("%s wins!\n", player2);
    } else {
        printf("It's a tie! No valid moves left for both players.\n");
    }
}