#include "pch.h"
#include "Dungeon_Item.h"

Dungeon_Item::Dungeon_Item(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::DUNGEON_ITEM, szMapPath, szScriptPath)
{
}

Dungeon_Item::~Dungeon_Item()
{
}

void Dungeon_Item::Awake()
{
	Dungeon::Awake();
}

void Dungeon_Item::Start()
{
	Dungeon::Start();
}

void Dungeon_Item::Update()
{
	Dungeon::Update();
}

void Dungeon_Item::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Dungeon_Item::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Dungeon_Item::Enter()
{
	Dungeon::Enter();
}

void Dungeon_Item::Exit()
{
	Dungeon::Exit();
}
