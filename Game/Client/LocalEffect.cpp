#include "pch.h"
#include "LocalEffect.h"

LocalEffect::LocalEffect()
	: GameObject(LAYER_TYPE::LOCAL_EFFECT)
{
}

LocalEffect::~LocalEffect()
{
}

void LocalEffect::Awake()
{
	GameObject::Awake();
}

void LocalEffect::Start()
{
	GameObject::Start();
}

void LocalEffect::Update()
{
	GameObject::Update();
}

void LocalEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void LocalEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
