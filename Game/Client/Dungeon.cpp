#include "pch.h"
#include "Dungeon.h"
#include "Scene.h"
#include "Scenes.h"
#include "DungeonEvent.h"

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
	EventUpdate();
}

void Dungeon::LateUpdate()
{
}

void Dungeon::FinalUpdate()
{
}

void Dungeon::AddEvent(shared_ptr<DungeonEvent> pDungeonEvent)
{
	m_qEventQueue.push(pDungeonEvent);
}

void Dungeon::EventUpdate()
{
	if (m_qEventQueue.empty())
		return;

	auto& pEvent = m_qEventQueue.front();
	pEvent->Update();

	if (pEvent->IsTrigger())
		m_qEventQueue.pop();
}
