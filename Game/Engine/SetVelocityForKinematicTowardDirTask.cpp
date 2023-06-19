#include "pch.h"
#include "SetVelocityForKinematicTowardDirTask.h"
#include "RigidBody.h"

SetVelocityForKinematicTowardDirTask::SetVelocityForKinematicTowardDirTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity)
	: BehaviorTask(pGameObject)
	, m_vVelocity(vVelocity)
{
}

SetVelocityForKinematicTowardDirTask::~SetVelocityForKinematicTowardDirTask()
{
}

BEHAVIOR_RESULT SetVelocityForKinematicTowardDirTask::Run()
{
	DIRECTION eDirection = m_pGameObject.lock()->GetDirection();
	Vec3 vVelocity = m_vVelocity;
	vVelocity.x = fabs(vVelocity.x);
	vVelocity.x = eDirection == DIRECTION::LEFT ? -vVelocity.x : vVelocity.x;
	m_pGameObject.lock()->GetRigidBody()->SetVelocity(vVelocity);
	return BEHAVIOR_RESULT::SUCCESS;
}
