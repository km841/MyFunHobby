#include "pch.h"
#include "UI.h"

UI::UI()
	: GameObject(LAYER_TYPE::UI)
{
}

UI::~UI()
{
}

void UI::Awake()
{
	GameObject::Awake();
}

void UI::Start()
{
	GameObject::Start();
}

void UI::Update()
{
	GameObject::Update();
}

void UI::LateUpdate()
{
	GameObject::LateUpdate();
}

void UI::FinalUpdate()
{
	GameObject::FinalUpdate();
}
