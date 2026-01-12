#include "Config.h"
#include "Define.h"

bool IsModuleEnabled()
{
    return sConfigMgr->GetOption<bool>("CatchupXP.Enable", false);
}

uint8 GetRequiredLevelDiff()
{
    return sConfigMgr->GetOption<uint8>("CatchupXP.LevelsBehindForCatchupXP", 5);
}

float GetMaxMultiplier()
{
    return sConfigMgr->GetOption<float>("CatchupXP.MaxMultiplier", 4.0f);
}
