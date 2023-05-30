#include "pch.h"
#include "DropItemHUD.h"

DropItemHUD::DropItemHUD()
	: m_iExitCount(0)
{
}

DropItemHUD::~DropItemHUD()
{
}

void DropItemHUD::Awake()
{
	HUD::Awake();
}

void DropItemHUD::Start()
{
	HUD::Start();
}

void DropItemHUD::Update()
{
	HUD::Update();
	if (m_iExitCount)
	{
		m_iExitCount--;
		Disable();
	}
}

void DropItemHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void DropItemHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void DropItemHUD::Action()
{
	m_iExitCount = 5;
}
