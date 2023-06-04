#include "pch.h"
#include "ObjectFadeInOutScript.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Clock.h"

ObjectFadeInOutScript::ObjectFadeInOutScript(float fDuration, FADE_TYPE eFadeType, float fStayTime)
	: m_eFadeType(eFadeType)
	, m_tStayTime(fStayTime)
	, m_tDuration(fDuration)
{
	m_tStayTime.Start();
}

ObjectFadeInOutScript::~ObjectFadeInOutScript()
{
}

void ObjectFadeInOutScript::LateUpdate()
{
	m_tStayTime.Update(OBJECT_DELTA_TIME);

	if (!m_tStayTime.IsFinished())
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
		if (m_tStayTime.IsFinished() && !m_tDuration.IsRunning())
		{
			m_tDuration.Start();
		}

		m_tDuration.Update(OBJECT_DELTA_TIME);

		if (!m_tDuration.IsFinished())
		{
			switch (m_eFadeType)
			{
			case FADE_TYPE::FADE_IN:
				GetMeshRenderer()->GetMaterial()->SetFloat(0, m_tDuration.GetProgress());
				break;
			case FADE_TYPE::FADE_OUT:
				GetMeshRenderer()->GetMaterial()->SetFloat(0, 1.f - m_tDuration.GetProgress());
				break;
			}
		}
	}

}
