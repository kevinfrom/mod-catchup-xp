#include "CatchupXPCommandScript.h"
#include "ScriptMgr.h"
#include "ChatCommand.h"
#include "Chat.h"
#include "ChatHelper.h"
#include "Utilities.h"
#include "StateHelper.h"
#include "Define.h"

using namespace Acore::ChatCommands;

CatchupXP_Command::CatchupXP_Command() : CommandScript("CatchupXP") {}

ChatCommandTable CatchupXP_Command::GetCommands() const
{
    static ChatCommandTable commandTable = {
        {"info", HandleInfo, SEC_PLAYER, Console::No},
        {"toggle", HandleToggle, SEC_PLAYER, Console::No}};

    static ChatCommandTable rootCommandTable = {
        {"catchupxp", commandTable}};

    return rootCommandTable;
}

bool CatchupXP_Command::HandleInfo(ChatHandler *handler)
{
    Player *player = GetPlayerFromChatHandler(handler);

    if (!player)
    {
        return false;
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

    return true;
}

bool CatchupXP_Command::HandleToggle(ChatHandler *handler)
{
    Player *player = GetPlayerFromChatHandler(handler);

    if (!player)
    {
        return false;
    }

    uint32 guid = GetPlayerGuid(player);

    if (PlayerDisabledCatchupXP(player))
    {
        CatchupXPDisabledPlayers.erase(guid);
        CharacterDatabase.Execute(
            "DELETE FROM character_catchup_xp_disabled WHERE guid = {}",
            guid);
        SendChatMessageToPlayer(player, "[CatchupXP] Catchup XP is now enabled");
    }
    else
    {
        CatchupXPDisabledPlayers.insert(guid);
        CharacterDatabase.Execute(
            "INSERT INTO character_catchup_xp_disabled (guid) VALUES ({})",
            guid);
        SendChatMessageToPlayer(player, "[CatchupXP] Catchup XP is now disabled");
    }

    return true;
}
