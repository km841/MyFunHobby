#include "pch.h"
#include "Background.h"

Background::Background()
	: GameObject(LAYER_TYPE::BACKGROUND)
{
}

Background::~Background()
{
}

void Background::Awake()
{
	GameObject::Awake();
}

void Background::Start()
{
	GameObject::Start();
}

void Background::Update()
{
	GameObject::Update();
}

void Background::LateUpdate()
{
	GameObject::LateUpdate();
}

void Background::FinalUpdate()
{
	GameObject::FinalUpdate();
}
