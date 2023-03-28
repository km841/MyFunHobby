#include "pch.h"
#include "HUD.h"

HUD::HUD()
	: GameObject(LAYER_TYPE::HUD)
{
}

HUD::~HUD()
{
}

void HUD::Awake()
{
	GameObject::Awake();
}

void HUD::Start()
{
	GameObject::Start();
}

void HUD::Update()
{
	GameObject::Update();
}

void HUD::LateUpdate()
{
	GameObject::LateUpdate();
}

void HUD::FinalUpdate()
{
	GameObject::FinalUpdate();
}
