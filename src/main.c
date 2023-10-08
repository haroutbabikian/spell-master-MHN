#include <stdio.h>
#include <stdlib.h>
#include "user_input.h"
#include "file_operations.h"
#include "game_logic.h"
#include "winner_determination.h"

int main() {
    char player1[MAX_NAME_LENGTH];
    char player2[MAX_NAME_LENGTH];
    char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
    int numSpells;

    numSpells = readSpells("spells.txt", spells);

    getPlayerNames(player1, player2);

    int startingPlayer = coinToss();

    char board[MAX_SPELLS][MAX_SPELL_LENGTH];
    int boardSize = 0;

    int winner = playGame(player1, player2, startingPlayer, spells, numSpells, board, &boardSize);

    announceWinner(player1, player2, winner);

    return 0;
}