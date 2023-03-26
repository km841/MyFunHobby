#include "pch.h"
#include "ObjectFadeInOutScript.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"

ObjectFadeInOutScript::ObjectFadeInOutScript(float fDuration, FADE_TYPE eFadeType, float fStayTime)
	: m_eFadeType(eFadeType)
	, m_tcStayTime(fStayTime)
	, m_tcDuration(fDuration)
{
	m_tcStayTime.Start();
}

ObjectFadeInOutScript::~ObjectFadeInOutScript()
{
}

void ObjectFadeInOutScript::LateUpdate()
{
	m_tcStayTime.Update(DELTA_TIME);

	if (!m_tcStayTime.IsFinished())
	{
		switch (m_eFadeType)
		{
		case FADE_TYPE::FADE_IN:
			GetMeshRenderer()->GetMaterial()->SetFloat(0, 0.01f);
			break;
		case FADE_TYPE::FADE_OUT:
			GetMeshRenderer()->GetMaterial()->SetFloat(0, 1.f);
			break;
		}
	}

	else
	{
		if (!m_tcStayTime.GetUnusedFlag())
		{
			m_tcStayTime.Disable();
			m_tcDuration.Start();
		}

		m_tcDuration.Update(DELTA_TIME);

		if (!m_tcDuration.IsFinished())
		{
			switch (m_eFadeType)
			{
			case FADE_TYPE::FADE_IN:
				GetMeshRenderer()->GetMaterial()->SetFloat(0, m_tcDuration.GetProgress());
				break;
			case FADE_TYPE::FADE_OUT:
				GetMeshRenderer()->GetMaterial()->SetFloat(0, 1.f - m_tcDuration.GetProgress());
				break;
			}
		}

		else
		{
			m_tcDuration.Disable();
		}
	}

}
