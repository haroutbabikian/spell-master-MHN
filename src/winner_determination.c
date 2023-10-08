#include <stdio.h>
#include "winner_determination.h"

void announceWinner(char player1[], char player2[], int winner) {
    if (winner == 0) {
        printf("%s wins! %s's move is invalid.\n", player1, player2);
    } else if (winner == 1) {
        printf("%s wins! %s's move is invalid.\n", player2, player1);
    } else {
        printf("It's a tie! No valid moves left for both players.\n");
    }
}