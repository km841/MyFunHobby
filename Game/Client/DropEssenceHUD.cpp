#include "pch.h"
#include "DropEssenceHUD.h"

DropEssenceHUD::DropEssenceHUD()
	: m_iExitCount(0)
{
}

DropEssenceHUD::~DropEssenceHUD()
{
}

void DropEssenceHUD::Awake()
{
	HUD::Awake();
}

void DropEssenceHUD::Start()
{
	HUD::Start();
}

void DropEssenceHUD::Update()
{
	HUD::Update();
	if (m_iExitCount)
	{
		m_iExitCount--;
		Disable();
	}
}

void DropEssenceHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void DropEssenceHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void DropEssenceHUD::Action()
{
	m_iExitCount = 5;
}
