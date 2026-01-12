#include "Define.h"
#include "ScriptMgr.h"

uint8 GetCurrentMaxLvlFromDatabase()
{
    QueryResult dbResult = CharacterDatabase.Query(
        "SELECT MAX(level) FROM characters");

    if (!dbResult)
    {
        return 1;
    }

    return (*dbResult)[0].Get<uint8>();
}
