#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#define MAX_SPELL_LENGTH 50
#define MAX_SPELLS 100

int isMoveValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize);

int isMoveValidBot(char spell[], char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize);

void addToBoard(char spell[], char board[][MAX_SPELL_LENGTH], int* boardSize);

void removeLastSpell(char board[][MAX_SPELL_LENGTH], int* boardSize);

int coinToss();

int playGame(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize);

#endif