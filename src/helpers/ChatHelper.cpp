#include "WorldSessionMgr.h"
#include "Player.h"
#include "Chat.h"

void SendChatMessageToAllPlayers(std::string message)
{
    sWorldSessionMgr->SendServerMessage(SERVER_MSG_STRING, message);
}

void SendChatMessageToPlayer(Player *player, std::string message)
{
    sWorldSessionMgr->SendServerMessage(SERVER_MSG_STRING, message, player);
}

Player *GetPlayerFromChatHandler(ChatHandler *handler)
{
    if (!handler || !handler->GetSession())
    {
        return nullptr;
    }

    return handler->GetSession()->GetPlayer();
}
