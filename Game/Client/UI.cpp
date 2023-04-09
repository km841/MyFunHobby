#include "pch.h"
#include "UI.h"

UI::UI()
	: Interface(LAYER_TYPE::UI)
{
}

UI::~UI()
{
}

void UI::Awake()
{
	Interface::Awake();
}

void UI::Start()
{
	Interface::Start();
}

void UI::Update()
{
	Interface::Update();
}

void UI::LateUpdate()
{
	Interface::LateUpdate();
}

void UI::FinalUpdate()
{
	Interface::FinalUpdate();
}
