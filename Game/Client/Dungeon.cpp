#include "pch.h"
#include "Dungeon.h"

Dungeon::Dungeon(DUNGEON_TYPE eDungeonType, const wstring& szMapPath)
	: m_eDungeonType(eDungeonType)
	, m_szMapPath(szMapPath)
{
}

Dungeon::~Dungeon()
{
}

void Dungeon::Awake()
{
}

void Dungeon::Start()
{
}

void Dungeon::Update()
{
}

void Dungeon::LateUpdate()
{
}

void Dungeon::FinalUpdate()
{
}
