#include "pch.h"
#include "DropSkulHUD.h"

DropSkulHUD::DropSkulHUD()
	: m_iExitCount(0)
{
}

DropSkulHUD::~DropSkulHUD()
{
}

void DropSkulHUD::Awake()
{
	HUD::Awake();
}

void DropSkulHUD::Start()
{
	HUD::Start();
}

void DropSkulHUD::Update()
{
	HUD::Update();
	if (m_iExitCount)
	{
		m_iExitCount--;
		Disable();
	}
}

void DropSkulHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void DropSkulHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void DropSkulHUD::Action()
{
	m_iExitCount = 5;
}