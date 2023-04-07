#include "pch.h"
#include "InterfaceEffect.h"

InterfaceEffect::InterfaceEffect()
	: GameObject(LAYER_TYPE::INTERFACE_EFFECT)
{
}

InterfaceEffect::~InterfaceEffect()
{
}

void InterfaceEffect::Awake()
{
	GameObject::Awake();
}

void InterfaceEffect::Start()
{
	GameObject::Start();
}

void InterfaceEffect::Update()
{
	GameObject::Update();
}

void InterfaceEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void InterfaceEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}
