#include "pch.h"
#include "Monster.h"
#include "Transform.h"
#include "Physical.h"
#include "Timer.h"


Monster::Monster()
{
	m_eLayerType = LAYER_TYPE::MONSTER;
}

Monster::~Monster()
{
}

void Monster::Awake()
{
	GameObject::Awake();
}

void Monster::Start()
{
	GameObject::Start();
}

void Monster::Update()
{
	GameObject::Update();
}

void Monster::LateUpdate()
{
	GameObject::LateUpdate();
}

void Monster::FinalUpdate()
{
	GameObject::FinalUpdate();
}

