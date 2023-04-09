#include "pch.h"
#include "HUD.h"

HUD::HUD()
	: Interface(LAYER_TYPE::HUD)
{
}

HUD::~HUD()
{
}

void HUD::Awake()
{
	Interface::Awake();
}

void HUD::Start()
{
	Interface::Start();
}

void HUD::Update()
{
	Interface::Update();
}

void HUD::LateUpdate()
{
	Interface::LateUpdate();
}

void HUD::FinalUpdate()
{
	Interface::FinalUpdate();
}
