#include "pch.h"
#include "HighWarlockBaseProjectile.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "ObjectReturnToPoolEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Monster.h"
#include "Transform.h"
#include "Physical.h"

POOL_INIT(HighWarlockBaseProjectile);
HighWarlockBaseProjectile::HighWarlockBaseProjectile()
	: m_bDespawn(false)
{
}

HighWarlockBaseProjectile::~HighWarlockBaseProjectile()
{
}

void HighWarlockBaseProjectile::Awake()
{
	PlayerProjectile::Awake();
}

void HighWarlockBaseProjectile::Start()
{
	PlayerProjectile::Start();
}

void HighWarlockBaseProjectile::Update()
{
	PlayerProjectile::Update();

	if (m_bDespawn)
	{
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
			m_bDespawn = false;
		}
	}
}

void HighWarlockBaseProjectile::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void HighWarlockBaseProjectile::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

void HighWarlockBaseProjectile::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
	{
		// 속도를 0으로 만들고 애니메이션 변경
		if (!m_bDespawn)
		{
			GetRigidBody()->SetVelocity(Vec3::Zero);
			GetAnimator()->Play(L"HighWarlock_BaseProjectile_Despawn", false);
			m_bDespawn = true;

			static_pointer_cast<Monster>(pGameObject)->FlagAsAttacked();
			pGameObject->GetStatus()->TakeDamage(1);

			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			vMyPos.z = 0.f;

			Vec3 vMonsterPos = pGameObject->GetTransform()->GetPhysicalPosition();
			vMonsterPos.z = 0.f;

			Vec3 vTargetVec = vMonsterPos - vMyPos;

			if (!pGameObject->GetStatus()->IsAlive())
			{
				if (vTargetVec.x > 0.f)
					static_pointer_cast<Monster>(pGameObject)->ActivateDeadEvent(PARTICLE_DIRECTION::RIGHT);
				else
					static_pointer_cast<Monster>(pGameObject)->ActivateDeadEvent(PARTICLE_DIRECTION::LEFT);
			}
		}
	}

	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->SetVelocity(Vec3::Zero);
		GetAnimator()->Play(L"HighWarlock_BaseProjectile_Despawn", false);
		m_bDespawn = true;
	}

}

void HighWarlockBaseProjectile::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
