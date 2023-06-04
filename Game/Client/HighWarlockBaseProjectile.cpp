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
#include "Clock.h"
#include "Engine.h"

POOL_INIT(HighWarlockBaseProjectile);
HighWarlockBaseProjectile::HighWarlockBaseProjectile()
	: m_bDespawn(false)
	, m_tLifeTimer(3.f)
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

	if (!m_tLifeTimer.IsRunning())
		m_tLifeTimer.Start();
	else
	{
		m_tLifeTimer.Update(OBJECT_DELTA_TIME);
	}

	if (m_tLifeTimer.IsFinished() && !m_bDespawn)
	{
		GetRigidBody()->SetVelocity(Vec3::Zero);
		GetAnimator()->Play(L"HighWarlock_BaseProjectile_Despawn", false);
		m_bDespawn = true;
	}

	if (m_bDespawn)
	{
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
			m_bDespawn = false;
			m_tLifeTimer.Reset();
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

		weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(pGameObject);

		if (MONSTER_STATE::DEAD == pMonster.lock()->GetMonsterState())
			return;

		if (!m_bDespawn)
		{
			GetRigidBody()->SetVelocity(Vec3::Zero);
			GetAnimator()->Play(L"HighWarlock_BaseProjectile_Despawn", false);
			m_bDespawn = true;

			static_pointer_cast<Monster>(pGameObject)->FlagAsAttacked();
			pGameObject->GetStatus()->TakeDamage(1);
			FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, 1.f, pGameObject->GetTransform()->GetPhysicalPosition());
			if (MONSTER_TYPE::NORMAL == pMonster.lock()->GetMonsterType())
				pMonster.lock()->SetMonsterState(MONSTER_STATE::WEAK_HIT);

			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
			vMyPos.z = 0.f;

			Vec3 vMonsterPos = pGameObject->GetTransform()->GetPhysicalPosition();
			vMonsterPos.z = 0.f;

			Vec3 vTargetVec = vMonsterPos - vMyPos;

			if (!pGameObject->GetStatus()->IsAlive())
			{
				vTargetVec.x *= 5.f;
				pMonster.lock()->SetMonsterState(MONSTER_STATE::DEAD);
				pMonster.lock()->ActivateDeadEvent(vTargetVec);
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
