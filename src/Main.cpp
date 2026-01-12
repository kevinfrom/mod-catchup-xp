#include "scripts/CatchupXPWorldScript.h"
#include "scripts/CatchupXPPlayerScript.h"
#include "scripts/CatchupXPCommandScript.h"

void AddCatchupXPScripts()
{
    new CatchupXP_World();
    new CatchupXP_Player();
    new CatchupXP_Command();
}
