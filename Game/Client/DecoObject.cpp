#include "pch.h"
#include "DecoObject.h"

DecoObject::DecoObject()
	: GameObject(LAYER_TYPE::DECO)
{
}

DecoObject::~DecoObject()
{
}

void DecoObject::Awake()
{
	GameObject::Awake();
}

void DecoObject::Start()
{
	GameObject::Start();
}

void DecoObject::Update()
{
	GameObject::Update();
}

void DecoObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void DecoObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}
