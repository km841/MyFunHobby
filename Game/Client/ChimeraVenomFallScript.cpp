#include "pch.h"
#include "ChimeraVenomFallScript.h"
#include "Chimera.h"
#include "Clock.h"
#include "VenomBallProjectile.h"
#include "ObjectFactory.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"
#include "Animation.h"
#include "Animator.h"
#include "RigidBody.h"
#include "VenomFall.h"

ChimeraVenomFallScript::ChimeraVenomFallScript()
	: m_bChecked(false)
{
}

ChimeraVenomFallScript::~ChimeraVenomFallScript()
{
}

void ChimeraVenomFallScript::LateUpdate()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(GetGameObject());

	if (MONSTER_STATE::SKILL2 == pChimera.lock()->GetMonsterState())
	{
		if (!m_bChecked)
		{
			// Venom Fall Create!
			CreateVenomFallAndAddedToScene();
			m_bChecked = true;
		}
	}
	else
	{
		m_bChecked = false;
	}
}

void ChimeraVenomFallScript::CreateVenomFallAndAddedToScene()
{
	shared_ptr<VenomFall> pProjectile =
		GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<VenomFall>(L"Forward");

	pProjectile->AddComponent(make_shared<Animator>());

	// Venom Fall Intro
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomFall_Intro", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_intro.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomFall_Intro", pAnimation);
	}

	// Venom Fall Loop
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomFall_Loop", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_loop.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomFall_Loop", pAnimation);
	}

	// Venom Fall Outro
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomFall_Outro", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_outro.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomFall_Outro", pAnimation);
	}

	pProjectile->GetAnimator()->Play(L"VenomFall_Intro", false);
	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos += Vec3(-350.f, 400.f, 0.f);
	pProjectile->GetTransform()->SetLocalPosition(vPos);

	pProjectile->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}

