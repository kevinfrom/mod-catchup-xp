#pragma once

#include "ScriptMgr.h"
#include "ChatCommand.h"
#include "Chat.h"

using namespace Acore::ChatCommands;

class CatchupXP_Command : public CommandScript
{
public:
    CatchupXP_Command();
    ChatCommandTable GetCommands() const override;
    static bool HandleInfo(ChatHandler *handler);
    static bool HandleToggle(ChatHandler *handler);
};
