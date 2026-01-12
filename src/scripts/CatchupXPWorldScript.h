#pragma once

#include "ScriptMgr.h"

class CatchupXP_World : public WorldScript
{
public:
    CatchupXP_World();
    void OnStartup() override;
};
