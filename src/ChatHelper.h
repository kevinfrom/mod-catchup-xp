#pragma once

#include "Player.h"
#include "Chat.h"

void SendChatMessageToAllPlayers(std::string message);
void SendChatMessageToPlayer(Player *player, std::string message);
Player *GetPlayerFromChatHandler(ChatHandler *handler);
