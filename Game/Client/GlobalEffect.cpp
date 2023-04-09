#include "pch.h"
#include "GlobalEffect.h"
#include "Clock.h"

GlobalEffect::GlobalEffect(float fEndTime)
	: GameObject(LAYER_TYPE::GLOBAL_EFFECT)
	, m_tDuration(fEndTime)
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
	if (m_tDuration.IsRunning())
		m_tDuration.Update(DELTA_TIME);
}

void GlobalEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void GlobalEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
