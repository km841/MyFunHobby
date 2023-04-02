#include "pch.h"
#include "ReturnHeadScript.h"
#include "LittleBone.h"
#include "Clock.h"
#include "Player.h"

ReturnHeadScript::ReturnHeadScript(weak_ptr<LittleBone> pLittleBone)
	: m_pLittleBone(pLittleBone)
	, m_tDuration(3.f)
{
	m_tDuration.Disable();
}

ReturnHeadScript::~ReturnHeadScript()
{
}

void ReturnHeadScript::LateUpdate()
{
	bool bUnusedFlag = m_tDuration.GetUnusedFlag();
	if (!m_pLittleBone.lock()->HasHead() && bUnusedFlag)
	{
		m_tDuration.Start();
	}

	else if (!bUnusedFlag && m_tDuration.IsRunning())
	{
		if (m_pLittleBone.lock()->HasHead())
			m_tDuration.Stop();
		else
			m_tDuration.Update(DELTA_TIME);
	}

	else if (!bUnusedFlag && m_tDuration.IsFinished())
	{
		m_pLittleBone.lock()->GetHead();
		m_pLittleBone.lock()->RefreshAnimation();

		m_tDuration.Disable();
	}
}
