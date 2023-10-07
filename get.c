#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

void getPlayerNames(char player1[MAX_NAME_LENGTH], char player2[MAX_NAME_LENGTH]) {
    printf("Enter name for Player 1 (no spaces allowed): ");
    scanf("%s", player1);

    printf("Enter name for Player 2 (no spaces allowed): ");
    scanf("%s", player2);
}


