#include "pch.h"
#include "Interface.h"

Interface::Interface(LAYER_TYPE eLayerType)
	: GameObject(eLayerType)
{
}

Interface::~Interface()
{
}

void Interface::Awake()
{
	GameObject::Awake();
}

void Interface::Start()
{
	GameObject::Start();
}

void Interface::Update()
{
	GameObject::Update();
}

void Interface::LateUpdate()
{
	GameObject::LateUpdate();
}

void Interface::FinalUpdate()
{
	GameObject::FinalUpdate();
}
