#include <stdio.h>
#include "user_input.h"

void getPlayerNames(char player1[], char player2[]) {
    printf("Enter the name of Player 1: ");
    scanf("%s", player1);
    printf("Enter the name of Player 2: ");
    scanf("%s", player2);
}

void getPlayerSpell(int currentPlayer, char spell[], char player1[], char player2[]) {
    printf("%s, enter your spell choice: ", (currentPlayer == 0) ? player1 : player2);
    scanf("%s", spell);
}
