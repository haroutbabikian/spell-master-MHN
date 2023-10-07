#ifndef USER_INPUT_H
#define USER_INPUT_H

// Function to obtain a player's spell choice and validate it
int getPlayerMove(const char** spells, int numSpells, const char* previousSpell, char* playerName);

#endif