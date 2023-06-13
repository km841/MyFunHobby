#include "pch.h"
#include "ChimeraBreathFireEffectScript.h"
#include "Clock.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"

ChimeraBreathFireEffectScript::ChimeraBreathFireEffectScript()
	: m_tDuration(1.5f)
	, m_vOrigin(Vec3(870.f, 440.f, 99.f))
{
}

ChimeraBreathFireEffectScript::~ChimeraBreathFireEffectScript()
{
}

void ChimeraBreathFireEffectScript::LateUpdate()
{
	if (!m_tDuration.IsRunning())
	{
		m_tDuration.Start();
	}

	else
	{
		m_tDuration.Update(WORLD_DELTA_TIME);
		float fRadian =  (1.f - m_tDuration.GetProgress()) * XM_PIDIV4 + (XM_PIDIV2 + XM_PIDIV4);
		Vec3 vRightVector = VEC3_RIGHT_NORMAL;
		Vec3 vRotated = Vec3(
			vRightVector.x * cosf(fRadian) + vRightVector.y * sinf(fRadian),
			vRightVector.x * sinf(fRadian) - vRightVector.y * cosf(fRadian),
			0.f
		);

		Vec3 vTarget = Vec3(50.f, 40.f, 0.f);
		GetTransform()->SetLocalPosition(m_vOrigin + vRotated * 150.f + vTarget * m_tDuration.GetProgress());
		GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRadian + XM_PIDIV4));
		if (m_tDuration.IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(GetGameObject(), eSceneType));
		}
	}
}
