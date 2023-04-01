#include "pch.h"
#include "CameraFadeInOutScript.h"
#include "Clock.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Camera.h"

CameraFadeInOutScript::CameraFadeInOutScript(shared_ptr<Camera> pCamera)
	: m_fAccTime(0.f)
	, m_fMaxTime(1.f)
	, m_ePrevCameraEffect(CAMERA_EFFECT::NONE)
	, m_pCamera(pCamera)
{
}

CameraFadeInOutScript::~CameraFadeInOutScript()
{
}

void CameraFadeInOutScript::LateUpdate()
{	
	CAMERA_EFFECT eCameraEffect = m_pCamera.lock()->GetCameraEffect();

	if (m_ePrevCameraEffect != eCameraEffect)
	{
		switch (eCameraEffect)
		{
		case CAMERA_EFFECT::FADE_IN:
			m_fAccTime = m_fMaxTime;
			break;
		case CAMERA_EFFECT::FADE_OUT:
			m_fAccTime = 0.f;
			break;
		}
	}

	if (CAMERA_EFFECT::FADE_OUT == eCameraEffect)
	{
		if (m_fAccTime < m_fMaxTime)
			m_fAccTime += DELTA_TIME;

		float fRatio = m_fAccTime / m_fMaxTime;

		if (fRatio > 1.f)
		{
			fRatio = 1.f;
			m_pCamera.lock()->RemoveCameraEffect();
		}

		GetGameObject()->GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	}

	else if (CAMERA_EFFECT::FADE_IN == eCameraEffect)
	{
		if (m_fAccTime > 0.f)
			m_fAccTime -= DELTA_TIME;

		float fRatio = m_fAccTime / m_fMaxTime;

		if (fRatio < 0.f)
		{
			fRatio = 0.f;
			m_pCamera.lock()->RemoveCameraEffect();
		}

		GetGameObject()->GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	}

	m_ePrevCameraEffect = eCameraEffect;
}
