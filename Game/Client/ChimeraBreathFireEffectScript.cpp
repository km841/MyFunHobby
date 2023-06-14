#include "pch.h"
#include "ChimeraBreathFireEffectScript.h"
#include "Clock.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "Animator.h"
#include "Animation.h"
#include "ChimeraBreathProjectile.h"
#include "ObjectFactory.h"

ChimeraBreathFireEffectScript::ChimeraBreathFireEffectScript()
	: m_tDuration(2.f)
	, m_vOrigin(Vec3(950.f, 490.f, 99.f))
	, m_bOutroFlag(false)
	, m_tBreathTick(0.075f)
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
		float fRadian =  (1.f - m_tDuration.GetProgress()) * XM_PIDIV2 + (XM_PIDIV2 + XM_PIDIV4);
		Vec3 vRightVector = VEC3_RIGHT_NORMAL;
		Vec3 vRotated = Vec3(
			vRightVector.x * cosf(fRadian) + vRightVector.y * sinf(fRadian),
			vRightVector.x * sinf(fRadian) - vRightVector.y * cosf(fRadian),
			0.f
		);

		Vec3 vTarget = Vec3(10.f, 2.f, 0.f);
		Vec3 vFinalPos = m_vOrigin + vRotated * 100.f + vTarget * m_tDuration.GetProgress();
		GetTransform()->SetLocalPosition(vFinalPos);
		GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRadian + XM_PIDIV4));

		if (!m_tBreathTick.IsRunning())
		{
			m_tBreathTick.Start();
		}
		else
		{
			m_tBreathTick.Update(WORLD_DELTA_TIME);

			if (m_tBreathTick.IsFinished() && !m_tDuration.IsFinished())
			{
				CreateBreathProjectileAndAddedToScene(vFinalPos, vRotated);
				m_tBreathTick.Reset();
			}
		}

		
		if (m_tDuration.IsFinished())
		{
			if (!m_bOutroFlag)
			{
				GetAnimator()->Play(L"Venom_Breath_Fire_Outro", false);
				m_bOutroFlag = true;
			}

			if (GetAnimator()->GetActiveAnimation()->IsFinished())
			{
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(GetGameObject(), eSceneType));
			}
		}
	}
}

void ChimeraBreathFireEffectScript::CreateBreathProjectileAndAddedToScene(const Vec3& vPos, const Vec3& vDir)
{
	shared_ptr<ChimeraBreathProjectile> pProjectile =
		GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<ChimeraBreathProjectile>(L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 30.f, 30.f), MassProperties());
	
	pProjectile->SetDirection(DIRECTION::LEFT);
	pProjectile->GetTransform()->SetLocalPosition(vPos);
	pProjectile->AddComponent(make_shared<Animator>());
	pProjectile->AddComponent(make_shared<DebugRenderer>());

	// Venom Projectile
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomProjectile", L"..\\Resources\\Animation\\Chimera\\chimera_venom_breath_projectile.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomProjectile", pAnimation);
	}

	// Venom Projectile Despawn
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomProjectile_Despawn", L"..\\Resources\\Animation\\Chimera\\chimera_venom_breath_projectile_despawn.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomProjectile_Despawn", pAnimation);
	}

	pProjectile->GetAnimator()->Play(L"VenomProjectile");
	pProjectile->Awake();
	pProjectile->GetRigidBody()->SetRotationZForDynamic(XM_PIDIV4);
	pProjectile->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, XM_PIDIV4));

	pProjectile->GetRigidBody()->SetLinearVelocityForDynamic(Conv::Vec3ToPxVec3(vDir * 600.f));
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}
