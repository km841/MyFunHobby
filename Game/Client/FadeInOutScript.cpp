#include "pch.h"
#include "FadeInOutScript.h"
#include "Timer.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"

FadeInOutScript::FadeInOutScript()
	: m_fAccTime(0.f)
	, m_fMaxTime(3.f)
	, m_bState(true)
{
}

FadeInOutScript::~FadeInOutScript()
{
}

void FadeInOutScript::LateUpdate()
{	
	if (m_bState)
	{
		if (m_fAccTime < m_fMaxTime)
			m_fAccTime += DELTA_TIME;
		
		else
			m_bState = false;
	}

	else
	{
		if (m_fAccTime > 0.f)
			m_fAccTime -= DELTA_TIME;
		
		else
			m_bState = true;
	}

	float fRatio = m_fAccTime / m_fMaxTime;

	GetGameObject()->GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
}
