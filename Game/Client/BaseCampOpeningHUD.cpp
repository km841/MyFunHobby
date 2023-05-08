#include "pch.h"
#include "BaseCampOpeningHUD.h"

BaseCampOpeningHUD::BaseCampOpeningHUD()
	: m_fInitSpeed(1000.f)
	, m_tDuration(5.f)
{
}

BaseCampOpeningHUD::~BaseCampOpeningHUD()
{
}

void BaseCampOpeningHUD::Awake()
{
	HUD::Awake();
}

void BaseCampOpeningHUD::Start()
{
	HUD::Start();
}

void BaseCampOpeningHUD::Update()
{
	HUD::Update();
}

void BaseCampOpeningHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void BaseCampOpeningHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}
