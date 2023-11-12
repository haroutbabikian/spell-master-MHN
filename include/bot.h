#ifndef BOT_H
#define BOT_H

#define MAX_SPELL_LENGTH 50

void initializeBot(int difficulty);

int chooseBotMoveEasy(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize);

int chooseBotMoveMedium(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize);

int chooseBotMoveHard(char spells[][MAX_SPELL_LENGTH], int numSpells, char board[][MAX_SPELL_LENGTH], int boardSize);

int playAgainstBot(char player1[], char player2[], int startingPlayer, char spells[][MAX_SPELL_LENGTH],
                   int numSpells, char board[][MAX_SPELL_LENGTH], int* boardSize);

#endif