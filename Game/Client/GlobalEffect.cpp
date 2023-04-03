#include "pch.h"
#include "GlobalEffect.h"

GlobalEffect::GlobalEffect()
	: GameObject(LAYER_TYPE::GLOBAL_EFFECT)
{
}

GlobalEffect::~GlobalEffect()
{
}

void GlobalEffect::Awake()
{
	GameObject::Awake();
}

void GlobalEffect::Start()
{
	GameObject::Start();
}

void GlobalEffect::Update()
{
	GameObject::Update();
}

void GlobalEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void GlobalEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
