#pragma once

#include "Define.h"
#include "Player.h"

extern uint8 currentMaxLvl;
extern std::unordered_set<uint32> CatchupXPDisabledPlayers;

bool PlayerDisabledCatchupXP(Player *player);
