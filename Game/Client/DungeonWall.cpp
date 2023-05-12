#include "pch.h"
#include "DungeonWall.h"

DungeonWall::DungeonWall(STAGE_KIND eStageKind)
	: GameObject(LAYER_TYPE::DUNGEON_WALL)
	, m_eStageKind(eStageKind)
{
}

DungeonWall::~DungeonWall()
{
}

void DungeonWall::Awake()
{
	GameObject::Awake();
}

void DungeonWall::Start()
{
	GameObject::Start();
}

void DungeonWall::Update()
{
	GameObject::Update();
}

void DungeonWall::LateUpdate()
{
	GameObject::LateUpdate();
}

void DungeonWall::FinalUpdate()
{
	GameObject::FinalUpdate();
}
