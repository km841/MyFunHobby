#include "pch.h"
#include "DarkMirror.h"
#include "ObjectFactory.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"

DarkMirror::DarkMirror()
	: GameObject(LAYER_TYPE::UNKNOWN)
{
}

DarkMirror::~DarkMirror()
{
}

void DarkMirror::Awake()
{
	GameObject::Awake();
}

void DarkMirror::Start()
{
	GameObject::Start();
}

void DarkMirror::Update()
{
	GameObject::Update();
}

void DarkMirror::LateUpdate()
{
	GameObject::LateUpdate();
}

void DarkMirror::FinalUpdate()
{
	GameObject::FinalUpdate();
}
