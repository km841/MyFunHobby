#include "pch.h"
#include "BossOpeningHUD.h"
#include "Clock.h"
#include "Engine.h"

BossOpeningHUD::BossOpeningHUD()
	:m_eStageKind(STAGE_KIND::END)
	, m_bAction(false)
	, m_tDuration(1.f)
	, m_tStayTimer(2.f)
{
}

BossOpeningHUD::~BossOpeningHUD()
{
}

void BossOpeningHUD::Awake()
{
	HUD::Awake();
}

void BossOpeningHUD::Start()
{
	HUD::Start();
}

void BossOpeningHUD::Update()
{
	HUD::Update();

	if (m_bAction)
	{
		if (!m_tStayTimer.IsRunning())
		{
			m_tStayTimer.Start();
			m_tDuration.Start();
		}

		else
		{
			m_tStayTimer.Update(WORLD_DELTA_TIME);

			if (m_tStayTimer.IsFinished())
			{
				m_tDuration.Update(WORLD_DELTA_TIME);

				switch (m_eStageKind)
				{
				case STAGE_KIND::BLACK_LAB:
					FONT->DrawString(L"뒤틀린 여신", 30.f, Vec3(1500.f, 140.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, Color::FromRGB(255, 255, 255, 1.f-m_tDuration.GetProgress()), FONT_ALIGN::CENTER);
					FONT->DrawString(L"키메라", 50.f, Vec3(1500.f, 100.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, Color::FromRGB(255, 255, 255, 1.f - m_tDuration.GetProgress()), FONT_ALIGN::CENTER);
					break;
				case STAGE_KIND::CITADEL_OF_FATE:
					break;
				}

				if (m_tDuration.IsFinished())
				{
					m_eStageKind = STAGE_KIND::END;
					m_tStayTimer.Reset();
					m_tDuration.Reset();
					m_bAction = false;
					Disable();
				}

			}

			else
			{
				switch (m_eStageKind)
				{
				case STAGE_KIND::BLACK_LAB:
					FONT->DrawString(L"뒤틀린 여신", 30.f, Vec3(1500.f, 140.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, 0xffffffff, FONT_ALIGN::CENTER);
					FONT->DrawString(L"키메라", 50.f, Vec3(1500.f, 100.f, 0.f), FONT_WEIGHT::ULTRA_BOLD, 0xffffffff, FONT_ALIGN::CENTER);
					break;
				case STAGE_KIND::CITADEL_OF_FATE:
					break;
				}
			}
		}
	}
}

void BossOpeningHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void BossOpeningHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void BossOpeningHUD::Action()
{
	assert(m_eStageKind != STAGE_KIND::END);
	m_bAction = true;
	Enable();

}

void BossOpeningHUD::SetStageKind(STAGE_KIND eStageKind)
{
	m_eStageKind = eStageKind;
}
