#pragma once
#include "DungeonEvent.h"
class Ch3ViceBossDungeon;
class CreateViceBossMapWallTileEvent :
    public DungeonEvent
{
public:
	CreateViceBossMapWallTileEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Ch3ViceBossDungeon> pDungeon);
	virtual ~CreateViceBossMapWallTileEvent();

public:
	virtual void Update();
	virtual void ExecuteEvent();

private:
	weak_ptr<Ch3ViceBossDungeon> m_pDungeon;
};

