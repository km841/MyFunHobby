#include "pch.h"
#include "DecoObject.h"

DecoObject::DecoObject(DECO_OBJECT_TYPE eDecoObjType)
	: GameObject(LAYER_TYPE::DECO)
	, m_eDecoObjType(eDecoObjType)
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
