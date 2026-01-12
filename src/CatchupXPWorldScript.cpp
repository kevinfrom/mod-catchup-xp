#include "CatchupXPWorldScript.h"
#include "ScriptMgr.h"
#include "ConfigHelper.h"
#include "DbHelper.h"
#include "StateHelper.h"
#include "Define.h"

CatchupXP_World::CatchupXP_World() : WorldScript("CatchupXP") {}

void CatchupXP_World::OnStartup()
{
    if (!IsModuleEnabled())
    {
        return;
    }

    uint8 tmpLvl = GetCurrentMaxLvlFromDatabase();
    if (tmpLvl > currentMaxLvl)
    {
        currentMaxLvl = tmpLvl;
    }
}
