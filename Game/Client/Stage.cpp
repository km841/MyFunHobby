#include "pch.h"
#include "Stage.h"
#include "Dungeon.h"
#include "Scene.h"
#include "Scenes.h"

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
		if (eDungeonType == pDungeon->GetDungeonType() && !pDungeon->IsVisited())
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

void Stage::AlignDungeons()
{
	// 최초 던전으로부터 중간에 상점을 지나 최종 던전까지 갈 수 있는 경로 탐색
	// visited 사용
	// 각 맵으로부터 게이트 정보를 가져온다
	// 각 던전의 타입, 던전 게이트 타입을 모두 알아야 한다.

	std::vector<DungeonInfo> vDungeonInfo = {};
	for (auto pDungeon : m_vDungeons)
	{
		std::vector<DUNGEON_TYPE> vDungeonTypes = GET_SINGLE(Scenes)->GetActiveScene()->GetDungeonGateTypesFromMapFile(pDungeon->GetMapPath());
		vDungeonInfo.push_back(std::make_tuple( false, vDungeonTypes, pDungeon ));
	}
	
	for (int32 i = 0; i < vDungeonInfo.size(); ++i)
	{
		std::vector<bool> vVisited(vDungeonInfo.size(), false);
		Weaving(i, vDungeonInfo, vVisited);
	}
	// 상점과 최종 맵을 제외한 나머지 맵들은 각각 위치에서 dfs를 실행한다
}

void Stage::Weaving(int32 iIndex, const std::vector<DungeonInfo>& vDungeonInfo, std::vector<bool>& vVisited)
{
	int32 iHalfSize = vDungeonInfo.size() / 2;
	vVisited[iIndex] = true;

	int32 iTotal = std::accumulate(vVisited.begin(), vVisited.end(), 0);
	if (iTotal >= 8)
		return;

	for (int32 i = 0; i < vDungeonInfo.size(); ++i)
	{
		if (std::get<2>(vDungeonInfo[i])->GetMapPath() ==
			std::get<2>(vDungeonInfo[iIndex])->GetMapPath())
			continue;

		if (vVisited[i])
			continue;

		const std::vector<DUNGEON_TYPE>& vDungeonTypes = std::get<1>(vDungeonInfo[i]);
		if (vDungeonTypes[0] == DUNGEON_TYPE::SHOP && abs(iHalfSize - i) > 1)
			continue;

		if (vDungeonTypes[0] == DUNGEON_TYPE::STAGE_BOSS && std::accumulate(vVisited.begin(), vVisited.end(), 0) > 8)
			break;
			
	}
}
