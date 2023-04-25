#include "pch.h"
#include "IsPlayerNearCondition.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

IsPlayerNearCondition::IsPlayerNearCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorCondition(pGameObject)
	, m_pPlayer(pPlayer)
{
}

IsPlayerNearCondition::~IsPlayerNearCondition()
{
}

BEHAVIOR_RESULT IsPlayerNearCondition::Run()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;

	if (vTargetVec.Length() < 50.f)
	{
		m_pGameObject.lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);

		if (vTargetVec.x > 0.f)
			m_pGameObject.lock()->SetDirection(DIRECTION::RIGHT);
		else
			m_pGameObject.lock()->SetDirection(DIRECTION::LEFT);
		

		return BEHAVIOR_RESULT::SUCCESS;
	}

	else
	{
		return BEHAVIOR_RESULT::FAILURE;
	}
}
