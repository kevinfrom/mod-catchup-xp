#pragma once

#include "ScriptMgr.h"
#include "Player.h"

class CatchupXP_Player : public PlayerScript
{
public:
    CatchupXP_Player();
    void OnPlayerLogin(Player *player) override;
    void OnPlayerLogout(Player *player) override;
    void OnPlayerLevelChanged(Player *player, uint8 /*oldLevel*/) override;
    void OnPlayerGiveXP(Player *player, uint32 &amount, Unit * /*victim*/, uint8 /*xpSource*/) override;
};
