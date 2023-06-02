#include "pch.h"
#include "TrackingOfMeleeTask.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"

TrackingOfMeleeTask::TrackingOfMeleeTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
	, m_pPlayer(pPlayer)
{
}

TrackingOfMeleeTask::~TrackingOfMeleeTask()
{
}

BEHAVIOR_RESULT TrackingOfMeleeTask::Run()
{
	uint8 iDirection = static_cast<uint8>(m_pGameObject.lock()->GetDirection());
	const Status* status = m_pGameObject.lock()->GetStatus();

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMonsterPos = m_pGameObject.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vTargetVec = vPlayerPos - vMonsterPos;
	Vec3 vTargetNormal = vTargetVec;
	vTargetNormal.Normalize();
	vTargetNormal.y = 0.f;
	vTargetNormal.z = 0.f;

	m_pGameObject.lock()->SetDirection(vTargetNormal.x < 0.f ? DIRECTION::LEFT : DIRECTION::RIGHT);
	m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(AXIS::X, vTargetNormal.x * status->fSpeed);

	if (status->fAttackDist > vTargetVec.Length())
	{
		return BEHAVIOR_RESULT::FAILURE;
	}

	return BEHAVIOR_RESULT::SUCCESS;
}
