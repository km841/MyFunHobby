#include "pch.h"
#include "Stage.h"
#include "Dungeon.h"

Stage::Stage(STAGE_KIND eStageKind)
	: m_eStageKind(eStageKind)
{
}

Stage::~Stage()
{
}

void Stage::Awake()
{
	for (int32 i = 0; i < m_vDungeons.size(); ++i)
	{
		if (m_vDungeons[i])
			m_vDungeons[i]->Awake();
	}

	// Select Active Dungeon!
	if (!m_vDungeons.empty())
		 m_pActiveDungeon = m_vDungeons[0];
}

void Stage::Start()
{
	if (m_pActiveDungeon.lock())
		m_pActiveDungeon.lock()->Start();
}

void Stage::Update()
{
	if (m_pActiveDungeon.lock())
		m_pActiveDungeon.lock()->Update();
}

void Stage::LateUpdate()
{
	if (m_pActiveDungeon.lock())
		m_pActiveDungeon.lock()->LateUpdate();
}

void Stage::FinalUpdate()
{
	if (m_pActiveDungeon.lock())
		m_pActiveDungeon.lock()->FinalUpdate();
}

void Stage::GoToNextDungeon(DUNGEON_TYPE eDungeonType)
{
	for (auto& pDungeon : m_vDungeons)
	{
		if (eDungeonType == pDungeon->GetDungeonType())
		{
			if (m_pActiveDungeon.lock())
				m_pActiveDungeon.lock()->Exit();

			m_pActiveDungeon = pDungeon;
			m_pActiveDungeon.lock()->Enter();
			break;
		}
	}
}

void Stage::AddDungeon(shared_ptr<Dungeon> pDungeon, const Vec4& vLimitRect)
{
	pDungeon->m_pStage = shared_from_this();

	if (Vec4::Zero != vLimitRect)
		pDungeon->SetLimitRect(vLimitRect);

	m_vDungeons.push_back(pDungeon);
}
