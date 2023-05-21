#include "pch.h"
#include "InfantryTackleTask.h"
#include "Transform.h"
#include "Monster.h"
#include "Player.h"
#include "Clock.h"
#include "RigidBody.h"

InfantryTackleTask::InfantryTackleTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
	, m_fDistance(500.f)
	, m_eDirection(DIRECTION::LEFT)
	, m_bInitDir(false)
{
}

BEHAVIOR_RESULT InfantryTackleTask::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;

	if (!m_bInitDir)
	{
		m_eDirection = vTargetVec.x < 0.f ? DIRECTION::LEFT : DIRECTION::RIGHT;
		m_bInitDir = true;
	}

	if (m_fDistance < 0.f)
	{
		m_fDistance = 500.f;
		m_pGameObject.lock()->SetDirection(m_eDirection);
		m_bInitDir = false;
		return BEHAVIOR_RESULT::SUCCESS;
	}

	else
	{
		const auto& status = m_pGameObject.lock()->GetStatus();
		m_fDistance -= 700.f * DELTA_TIME;
		m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(DIRECTION::LEFT == m_eDirection ? -700.f : 700.f, 0.f, 0.f));
	}

	return BEHAVIOR_RESULT::FAILURE;
}
