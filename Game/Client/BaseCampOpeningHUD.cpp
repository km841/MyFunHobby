#include "pch.h"
#include "BaseCampOpeningHUD.h"
#include "Clock.h"
#include "Transform.h"
#include "Engine.h"

BaseCampOpeningHUD::BaseCampOpeningHUD()
	: m_tUpTimer(0.7f)
	, m_tDownTimer(0.7f)
	, m_tStayTimer(2.f)
	, m_fSpeed(300.f)
	, m_fHudSpeed(m_fSpeed * 15.f)
	, m_bActionFlag(false)
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
	if (m_bActionFlag)
	{
		UpdateAction();
	}
}

void BaseCampOpeningHUD::LateUpdate()
{
	HUD::LateUpdate();
}

void BaseCampOpeningHUD::FinalUpdate()
{
	HUD::FinalUpdate();
}

void BaseCampOpeningHUD::Action()
{
	m_bActionFlag = true;
	Enable();
}

void BaseCampOpeningHUD::UpdateAction()
{
	// 위에서 내려와서 n초 있다가 올라가는 모션

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	if (!m_tDownTimer.IsRunning())
	{
		m_tDownTimer.Start();
		m_tStayTimer.Start();
		m_tUpTimer.Start();
		GetTransform()->SetLocalPosition(Vec3(fWidth / 2.f, fHeight, 50.f));
	}

	else if (!m_tDownTimer.IsFinished())
	{
		m_tDownTimer.Update(WORLD_DELTA_TIME);
		const Vec3& vMyPos = GetTransform()->GetLocalPosition();

		GetTransform()->SetLocalPosition(Vec3(vMyPos.x, vMyPos.y - m_fSpeed * OBJECT_DELTA_TIME, vMyPos.z));
	}

	else if (m_tDownTimer.IsFinished() && !m_tStayTimer.IsFinished())
	{
		if (!m_tStayTimer.IsRunning())
			m_tStayTimer.Start();

		m_tStayTimer.Update(WORLD_DELTA_TIME);
	}

	else if (m_tStayTimer.IsFinished())
	{
		if (!m_tUpTimer.IsRunning())
			m_tUpTimer.Start();

		m_tUpTimer.Update(WORLD_DELTA_TIME);
		const Vec3& vMyPos = GetTransform()->GetLocalPosition();
		GetTransform()->SetLocalPosition(Vec3(vMyPos.x, vMyPos.y + m_fSpeed * WORLD_DELTA_TIME, vMyPos.z));


	}

	else if (m_tUpTimer.IsFinished())
	{
		m_bActionFlag = false;
		Disable();
	}
}
