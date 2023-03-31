#include "pch.h"
#include "LittleBone.h"

LittleBone::LittleBone()
	: Skul(SKUL_GRADE::NORMAL)
{
}

void LittleBone::Awake()
{
	GameObject::Awake();
}

void LittleBone::Start()
{
	GameObject::Start();
}

void LittleBone::Update()
{
	GameObject::Update();
}

void LittleBone::LateUpdate()
{
	GameObject::LateUpdate();
}

void LittleBone::FinalUpdate()
{
	GameObject::FinalUpdate();
}
