#include "CatchupXPWorldScript.h"
#include "ScriptMgr.h"
#include "Define.h"
#include "../helpers/ConfigHelper.h"
#include "../helpers/DbHelper.h"
#include "../helpers/StateHelper.h"

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
