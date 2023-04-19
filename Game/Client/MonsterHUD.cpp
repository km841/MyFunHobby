#include "pch.h"
#include "MonsterHUD.h"

MonsterHUD::MonsterHUD(shared_ptr<Monster> pMonster)
	: GameObject(LAYER_TYPE::MONSTER_HUD)
	, m_pMonster(pMonster)
{
}

MonsterHUD::~MonsterHUD()
{
}

void MonsterHUD::Awake()
{
	GameObject::Awake();
}

void MonsterHUD::Start()
{
	GameObject::Start();
}

void MonsterHUD::Update()
{
	GameObject::Update();
}

void MonsterHUD::LateUpdate()
{
	GameObject::LateUpdate();
}

void MonsterHUD::FinalUpdate()
{
	GameObject::FinalUpdate();
}
