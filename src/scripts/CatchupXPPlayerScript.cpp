#include "CatchupXPPlayerScript.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "../helpers/ConfigHelper.h"
#include "../helpers/StateHelper.h"
#include "../helpers/ChatHelper.h"

CatchupXP_Player::CatchupXP_Player() : PlayerScript("CatchupXP") {}

void CatchupXP_Player::OnPlayerLogin(Player *player)
{
    if (!IsModuleEnabled())
    {
        return;
    }

    uint32 guid = GetPlayerGuid(player);

    QueryResult dbResult = CharacterDatabase.Query(
        "SELECT 1 "
        "FROM character_catchup_xp_disabled "
        "WHERE guid = {}",
        guid);

    if (dbResult)
    {
        CatchupXPDisabledPlayers.insert(guid);
        SendChatMessageToPlayer(player, "[CatchupXP] You have disabled Catchup XP. To toggle Catchup XP use: .catchup toggle");

        return;
    }

    float mult = GetCatchupXPMultiplier(player);
    SendChatMessageToPlayer(player, Acore::StringFormat("[CatchupXP] Your XP multiplier: {:.2f}x (current server max level is {})", mult, currentMaxLvl));
}

void CatchupXP_Player::OnPlayerLogout(Player *player)
{
    CatchupXPDisabledPlayers.erase(GetPlayerGuid(player));
}

void CatchupXP_Player::OnPlayerLevelChanged(Player *player, uint8 /*oldLevel*/)
{
    if (!IsModuleEnabled() || player->IsGameMaster())
    {
        return;
    }

    uint8 lvl = player->GetLevel();
    if (lvl > currentMaxLvl)
    {
        currentMaxLvl = lvl;
        SendChatMessageToAllPlayers(Acore::StringFormat("[CatchupXP] Current max level increased: {}", currentMaxLvl));
    }

    float mult = GetCatchupXPMultiplier(player);
    SendChatMessageToPlayer(player, Acore::StringFormat("[CatchupXP] Your XP multiplier: {:.2f}x (current server max level is {})", mult, currentMaxLvl));

    if (PlayerDisabledCatchupXP(player))
    {
        SendChatMessageToPlayer(player, "[CatchupXP] Catchup XP is disabled");
    }
    else
    {
        SendChatMessageToPlayer(player, "[CatchupXP] Catchup XP is enabled");
    }
}

void CatchupXP_Player::OnPlayerGiveXP(Player *player, uint32 &amount, Unit * /*victim*/, uint8 /*xpSource*/)
{
    if (!IsModuleEnabled() || PlayerDisabledCatchupXP(player) || player->IsGameMaster())
    {
        return;
    }

    // Multiply the XP amount
    amount = uint32(float(amount) * GetCatchupXPMultiplier(player));
}
