#include "pch.h"
#include "MapReward.h"

MapReward::MapReward(GRADE eGrade)
	: GameObject(LAYER_TYPE::MAP_REWARD)
	, m_eGrade(eGrade)
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
