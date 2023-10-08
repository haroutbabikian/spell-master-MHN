#ifndef SPELL_MASTER_H
#define SPELL_MASTER_H

#include <stdio.h>
#include <stdlib.h>

int coin_toss();

int getPlayerMove(const char** spells, int numSpells, const char* previousSpell, char* playerName);

#endif /* SPELL_MASTER_H */