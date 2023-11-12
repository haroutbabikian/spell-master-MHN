#include <stdio.h>
#include "winner_determination.h"



// Announces the winner of the game.
// Parameters:
// player1: A character array containing the name of Player 1.
// player2: A character array containing the name of Player 2 or "Bot".
// winner: An integer indicating the winner (0 for Player 1, 1 for Player 2, -1 for a tie).
// Effects:
// Prints the name of the winning player or announces a tie if there's no winner.
void announceWinner(char player1[], char player2[], int winner) {
    if (winner == 0) {
        printf("%s wins!\n", player1);
    } else if (winner == 1) {
        printf("%s wins!\n", player2);
    } else {
        printf("It's a tie! No valid moves left for both players.\n");
    }
}