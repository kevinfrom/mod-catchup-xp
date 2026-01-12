#include "CatchupXPWorldScript.h"
#include "CatchupXPPlayerScript.h"
#include "CatchupXPCommandScript.h"

void AddCatchupXPScripts()
{
    new CatchupXP_World();
    new CatchupXP_Player();
    new CatchupXP_Command();
}
