#include "pch.h"
#include "MapReward.h"

MapReward::MapReward(GRADE eGrade)
	: GameObject(LAYER_TYPE::MAP_REWARD)
	, m_eGrade(eGrade)
	, m_bTaked(false)
	, m_bIsCollisionWithPlayer(false)
{
}

MapReward::~MapReward()
{
}

void MapReward::Awake()
{
	GameObject::Awake();
}

void MapReward::Start()
{
	GameObject::Start();
}

void MapReward::Update()
{
	GameObject::Update();
}

void MapReward::LateUpdate()
{
	GameObject::LateUpdate();
}

void MapReward::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void MapReward::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void MapReward::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}