#include "pch.h"
#include "ChimeraVenomBallScript.h"
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

ChimeraVenomBallScript::ChimeraVenomBallScript()
	: m_iVenomBallCount(0)
	, m_tDuration(1.f)
{
}

ChimeraVenomBallScript::~ChimeraVenomBallScript()
{
}

void ChimeraVenomBallScript::LateUpdate()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(GetGameObject());

	if (MONSTER_STATE::SKILL1 == pChimera.lock()->GetMonsterState())
	{
		// Timer 걸어두고 타이머가 끝날 때 애니메이션 클리어
		if (!m_tDuration.IsRunning())
		{
			m_tDuration.Start();
			CreateVenomBallAndAddedToScene();
			pChimera.lock()->ClearAnimation();
		}
		else
		{
			m_tDuration.Update(WORLD_DELTA_TIME);

			if (m_tDuration.IsFinished())
			{
				m_tDuration.Reset();
				pChimera.lock()->ClearAnimation();
				m_iVenomBallCount++;

				if (m_iVenomBallCount >= 3)
				{
					pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL1_END);
					m_iVenomBallCount = 0;
				}
			}
		}
	}
	else
	{
		m_iVenomBallCount = 0;
	}
}

void ChimeraVenomBallScript::CreateVenomBallAndAddedToScene()
{
	shared_ptr<VenomBallProjectile> pProjectile =
		GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VenomBallProjectile>(L"Forward", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties());
	
	pProjectile->AddComponent(make_shared<Animator>());

	// Venom Ball Loop
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomBall", L"..\\Resources\\Animation\\Chimera\\chimera_venom_ball.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomBall", pAnimation);
		
	}

	// Venom Ball Despawn
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomBall_Despawn", L"..\\Resources\\Animation\\Chimera\\chimera_venom_ball_despawn.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomBall_Despawn", pAnimation);
	}

	pProjectile->GetAnimator()->Play(L"VenomBall");
	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos += Vec3(-100.f, 450.f, 0.f);
	pProjectile->GetTransform()->SetLocalPosition(vPos);

	PxVec3 vDir = PxVec3(-1.f, 1.f, 0.f);
	vDir.normalize();

	pProjectile->GetRigidBody()->SetLinearVelocityForDynamic(vDir * static_cast<int32>(RANDOM(550, 750)));

	pProjectile->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}
