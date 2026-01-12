#include "Define.h"
#include "Player.h"
#include "Utilities.h"

uint8 currentMaxLvl = 1;
std::unordered_set<uint32> CatchupXPDisabledPlayers;

bool PlayerDisabledCatchupXP(Player *player)
{
    return CatchupXPDisabledPlayers.contains(
        GetPlayerGuid(player));
}
