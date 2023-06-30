#include "pch.h"
#include "EndingHUD.h"
#include "Clock.h"
#include "Resources.h"
#include "Scenes.h"
#include "ComponentObject.h"
#include "SoundSource.h"
#include "Engine.h"

EndingHUD::EndingHUD()
	: m_tStayTimer(4.f)
	, m_tCommentStayTimer(2.f)
	, m_tCommentTimer(3.f)
	, m_bAudioStart(false)
{
}

EndingHUD::~EndingHUD()
{
}

void EndingHUD::Awake()
{
	HUD::Awake();
}

void EndingHUD::Start()
{
	HUD::Start();
}

void EndingHUD::Update()
{
	HUD::Update();

	if (m_tStayTimer.IsRunning())
	{
		m_tStayTimer.Update(WORLD_DELTA_TIME);

		if (m_tStayTimer.IsFinished())
		{
			Enable();

			if (!m_bAudioStart)
			{
				SCENE_SOUND->SetBGMClip(GET_SINGLE(Resources)->Load<Sound>(L"EndingBGM", L"..\\Resources\\Sound\\SkulStory7_Ending_Epilogue.wav"));
				SCENE_SOUND->PlayBGM();

				shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"BigSound", L"..\\Resources\\Sound\\Hero_Landing.wav");
				SCENE_SOUND->SetClip(pSound);
				SCENE_SOUND->Play();
				m_bAudioStart = true;
				m_tCommentStayTimer.Start();
			}

			m_tCommentStayTimer.Update(WORLD_DELTA_TIME);
			if (m_tCommentStayTimer.IsRunning() && m_tCommentStayTimer.IsFinished())
			{
				m_tCommentTimer.Update(WORLD_DELTA_TIME);
				float fProgress = m_tCommentTimer.GetProgress();
				FONT->DrawString(L"끝까지 시청해주셔서 감사합니다!", 30.f, Vec3(825.f, 180.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, Color::FromRGB(250, 210, 160, fProgress));
				FONT->DrawString(L"Made by 44기 김현모", 25.f, Vec3(825.f, 135.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, Color::FromRGB(255, 255, 255, fProgress));
			}
		}
	}
}

void EndingHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void EndingHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void EndingHUD::Action()
{
	m_tStayTimer.Start();
	m_tCommentTimer.Start();
}
