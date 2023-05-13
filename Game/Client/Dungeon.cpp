#include "pch.h"
#include "Dungeon.h"
#include "Scene.h"
#include "Scenes.h"
#include "DungeonEvent.h"
#include "IfAlwaysTrue.h"
#include "IfAllDeadMonsterInDungeon.h"
#include "MonsterSpawnDungeonEvent.h"
#include "PlayerTeleportEvent.h"
#include "IfPlayerPosXExceedsN.h"
#include "DungeonGateOpenEvent.h"
#include "CreateMapRewardEvent.h"
#include "IfTakedMapReward.h"

Dungeon::Dungeon(DUNGEON_TYPE eDungeonType, const wstring& szMapPath, const wstring& szScriptPath)
	: m_eDungeonType(eDungeonType)
	, m_szMapPath(szMapPath)
{
    if (L"" != szScriptPath)
        LoadEventFromFile(szScriptPath);
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

void Dungeon::Enter()
{
    if (!m_szMapPath.empty())
        GET_SINGLE(Scenes)->GetActiveScene()->Load(m_szMapPath);

    GET_SINGLE(Scenes)->GetActiveScene()->RegisterSceneEvent(EVENT_TYPE::SCENE_FADE_EVENT, static_cast<uint8>(SCENE_FADE_EFFECT::FADE_IN), 1.f);
}

void Dungeon::Exit()
{
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::TILE);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::BACKGROUND);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::DUNGEON_GATE);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::DUNGEON_WALL);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::MAP_REWARD);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::DECO);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::PARTICLE);
    GET_SINGLE(Scenes)->GetActiveScene()->RemoveLocalGroup(LAYER_TYPE::DROP_ESSENCE);
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

void Dungeon::LoadEventFromFile(const wstring& szEventScriptPath)
{
    std::wifstream ifs(szEventScriptPath, std::ios::in);

    uint32 iEventCount = 0;
    ifs >> iEventCount;

    for (uint32 i = 0; i < iEventCount; ++i)
    {
        int32 iEventKind = 0;
        ifs >> iEventKind;
        DUNGEON_EVENT_KIND eEventKind = static_cast<DUNGEON_EVENT_KIND>(iEventKind);
        ifs.ignore(1);

        int32 iCondition = 0;
        ifs >> iCondition;
        CONDITION_TYPE eCondition = static_cast<CONDITION_TYPE>(iCondition);
        ifs.ignore(1);

        int32 iEnum1 = 0;
        int32 iEnum2 = 0;

        ifs >> iEnum1;
        ifs.ignore(1);
        ifs >> iEnum2;
        ifs.ignore(1);

        Vec3 vVec3 = {};
        ifs >> vVec3.x >> vVec3.y >> vVec3.z;
        ifs.ignore(1);


        shared_ptr<ConditionBlock> pConditionBlock = nullptr;
        switch (eCondition)
        {
        case CONDITION_TYPE::ALWAYS_TRUE:
            pConditionBlock = make_shared<IfAlwaysTrue>();
            break;
        case CONDITION_TYPE::ALL_MONSTER_DEAD_IN_DUNGEON:
            pConditionBlock = make_shared<IfAllDeadMonsterInDungeon>();
            break;

        case CONDITION_TYPE::PLAYER_POS_X_EXCEEDS_800:
            pConditionBlock = make_shared<IfPlayerPosXExceedsN>(800.f);
            break;

        case CONDITION_TYPE::PLAYER_POS_X_EXCEEDS_1000:
            pConditionBlock = make_shared<IfPlayerPosXExceedsN>(1000.f);
            break;

        case CONDITION_TYPE::TAKE_MAP_REWARD:
            pConditionBlock = make_shared<IfTakedMapReward>();
            break;
        }
        assert(pConditionBlock);


        shared_ptr<DungeonEvent> pDungeonEvent = nullptr;
        switch (eEventKind)
        {
        case DUNGEON_EVENT_KIND::MONSTER_SPAWN:
            pDungeonEvent = make_shared<MonsterSpawnDungeonEvent>(pConditionBlock, static_cast<MONSTER_KIND>(iEnum1), vVec3);
            break;
        case DUNGEON_EVENT_KIND::CREATE_MAP_REWARD:
            pDungeonEvent = make_shared<CreateMapRewardEvent>(pConditionBlock, static_cast<GRADE>(iEnum1), m_eDungeonType );
            break;
        case DUNGEON_EVENT_KIND::PLAYER_TELEPORT:
            pDungeonEvent = make_shared<PlayerTeleportEvent>(pConditionBlock, vVec3);
            break;
        case DUNGEON_EVENT_KIND::DUNGEON_GATE_OPEN:
            pDungeonEvent = make_shared<DungeonGateOpenEvent>(pConditionBlock);
        }
        assert(pDungeonEvent);

        AddEvent(pDungeonEvent);
    }

    ifs.close();
}
