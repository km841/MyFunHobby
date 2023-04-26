#include "pch.h"
#include "ComponentObject.h"

ComponentObject::ComponentObject()
	: GameObject(LAYER_TYPE::COMPONENT_OBJECT)
{
}

ComponentObject::~ComponentObject()
{
}

void ComponentObject::Awake()
{
	GameObject::Awake();
}

void ComponentObject::Start()
{
	GameObject::Start();
}

void ComponentObject::Update()
{
	GameObject::Update();
}

void ComponentObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void ComponentObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}
