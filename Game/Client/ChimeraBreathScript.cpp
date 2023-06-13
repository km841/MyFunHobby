#include "pch.h"
#include "ChimeraBreathScript.h"
#include "Chimera.h"
#include "Clock.h"
#include "ObjectFactory.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"
#include "Animation.h"
#include "Animator.h"
#include "RigidBody.h"
#include "LocalEffect.h"
#include "ChimeraBreathFireEffectScript.h"

ChimeraBreathScript::ChimeraBreathScript()
	: m_bChecked(false)
	, m_tBreathTick(0.2f)
{
}

ChimeraBreathScript::~ChimeraBreathScript()
{
}

void ChimeraBreathScript::LateUpdate()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(GetGameObject());

	if (MONSTER_STATE::SKILL4 == pChimera.lock()->GetMonsterState())
	{
		if (!m_bChecked)
		{
			CreateBreathFireAndAddedToScene();
			m_bChecked = true;
		}

		if (!m_tBreathTick.IsRunning())
			m_tBreathTick.Start();
		else
		{
			m_tBreathTick.Update(WORLD_DELTA_TIME);
			if (m_tBreathTick.IsFinished())
			{
				float fRadian = m_tBreathTick.GetProgress() * (1.f-XM_PI);
				CreateBreathProjectileAddedToScene(fRadian);
			}
		}
	}
	else
	{
		m_bChecked = false;
		m_tBreathTick.Reset();
	}
	// <Enter>
	// Create Breath Fire Animation
	// 
	// <Loop>
	// Create Breath Projectile
}

void ChimeraBreathScript::CreateBreathFireAndAddedToScene()
{
	// 시간이 지남에 따라 각도가 돌아감
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<LocalEffect>(L"Forward");
	pLocalEffect->AddComponent(make_shared<ChimeraBreathFireEffectScript>());
	pLocalEffect->AddComponent(make_shared<Animator>());

	// Breath Fire Animation
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Venom_Breath_Fire", L"..\\Resources\\Animation\\Chimera\\chimera_venom_breath_fire.anim");
		pLocalEffect->GetAnimator()->AddAnimation(L"Venom_Breath_Fire", pAnimation);
	}

	// Breath Fire Outro Animation
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Venom_Breath_Fire_Outro", L"..\\Resources\\Animation\\Chimera\\chimera_venom_breath_fire_outro.anim");
		pLocalEffect->GetAnimator()->AddAnimation(L"Venom_Breath_Fire_Outro", pAnimation);
	}

	pLocalEffect->GetAnimator()->Play(L"Venom_Breath_Fire");
	pLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
}

void ChimeraBreathScript::CreateBreathProjectileAddedToScene(float fRadian)
{
}
