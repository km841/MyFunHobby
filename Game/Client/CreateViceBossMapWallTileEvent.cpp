#include "pch.h"
#include "CreateViceBossMapWallTileEvent.h"
#include "Ch3ViceBossDungeon.h"

CreateViceBossMapWallTileEvent::CreateViceBossMapWallTileEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Ch3ViceBossDungeon> pDungeon)
	: DungeonEvent(DUNGEON_EVENT_KIND::VICE_CREATE_TILE, pConditionBlock)
	, m_pDungeon(pDungeon)
{
}

CreateViceBossMapWallTileEvent::~CreateViceBossMapWallTileEvent()
{
}

void CreateViceBossMapWallTileEvent::Update()
{
	DungeonEvent::Update();
}

void CreateViceBossMapWallTileEvent::ExecuteEvent()
{
	m_pDungeon.lock()->CreateWallTilesAndAddedToScene();
}
