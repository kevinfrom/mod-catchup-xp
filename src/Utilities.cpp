#include "Define.h"
#include "Player.h"
#include "StateHelper.h"
#include "ConfigHelper.h"

uint8 GetPlayerGuid(Player *player)
{
    return player->GetGUID().GetCounter();
}

float GetCatchupXPMultiplier(Player *player)
{
    uint8 lvl = player->GetLevel();

    uint8 requiredLevelDiff = GetRequiredLevelDiff();
    float maxMultiplier = GetMaxMultiplier();

    // If current max level is less than the required level diff, don't apply a multiplier
    if (currentMaxLvl <= requiredLevelDiff)
    {
        return 1.0f;
    }

    // If player's level is not far enough behind, dont apply a multiplier
    if (lvl + requiredLevelDiff >= currentMaxLvl)
    {
        return 1.0f;
    }

    // Calculate the multiplier based on far behind the player is
    float t = float(currentMaxLvl - lvl - requiredLevelDiff) / float(currentMaxLvl - requiredLevelDiff - 1);
    t = std::clamp(t, 0.0f, 1.0f);

    return 1.0f + (maxMultiplier - 1.0f) * t;
}
