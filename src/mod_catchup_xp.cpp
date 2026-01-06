#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"

uint8 maxLvl = 1;

class CatchupXP_World : public WorldScript
{
public:
    CatchupXP_World(): WorldScript("CatchupXP") { }

    void OnStartup()
    {
        QueryResult r = CharacterDatabase.Query(
            "SELECT MAX(level) FROM characters"
        );

        if (r)
        {
            maxLvl = (*r)[0].Get<uint8>();
        }
    }
};

class CatchupXP_Player : public PlayerScript
{
public:
    CatchupXP_Player(): PlayerScript("CatchupXP") { }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldLevel*/)
    {
        uint8 lvl = player->GetLevel();
        if (lvl > maxLvl)
        {
            maxLvl = lvl;
        }
    }

    void OnPlayerGiveXP(Player* player, uint32& amount, Unit* /*victim*/, uint8 /*xpSource*/)
    {
        if (!sConfigMgr->GetOption<bool>("CatchupXP.Enable", false))
        {
            return;
        }

        uint8 lvl = player->GetLevel();
        uint8 requiredLevelDiff = sConfigMgr->GetOption<uint8>("CatchupXP.LevelsBehindForCatchupXP", 5);
        float maxMultiplier = sConfigMgr->GetOption<float>("CatchupXP.MaxMultiplier", 4.0);

        // Calculate the multiplier based on far behind the player is
        float t = float(maxLvl - lvl - requiredLevelDiff) / float(maxLvl - requiredLevelDiff - 1);
        t = std::clamp(t, 0.0f, 1.0f);
        float multiplier = 1.0f + (maxMultiplier - 1.0f) * t;

        amount *= multiplier;
    }
};

void AddCatchupXPScripts()
{
    new CatchupXP_World();
    new CatchupXP_Player();
}
