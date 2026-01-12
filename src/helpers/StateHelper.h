#pragma once

#include "Define.h"
#include "Player.h"

extern uint8 currentMaxLvl;
extern std::unordered_set<uint32> CatchupXPDisabledPlayers;

uint8 GetPlayerGuid(Player *player);
bool PlayerDisabledCatchupXP(Player *player);
float GetCatchupXPMultiplier(Player *player);
