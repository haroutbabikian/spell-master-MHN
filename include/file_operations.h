#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#define MAX_SPELL_LENGTH 50
#define MAX_SPELLS 100

int readSpells(const char* filename, char spells[][MAX_SPELL_LENGTH]);
void displaySpells(char spells[][MAX_SPELL_LENGTH], int numSpells);

#endif