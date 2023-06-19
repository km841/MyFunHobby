#include "pch.h"
#include "SetVelocityForKinematicOpposedDirTask.h"
#include "RigidBody.h"

SetVelocityForKinematicOpposedDirTask::SetVelocityForKinematicOpposedDirTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity)
	: BehaviorTask(pGameObject)
	, m_vVelocity(vVelocity)
{
}

SetVelocityForKinematicOpposedDirTask::~SetVelocityForKinematicOpposedDirTask()
{
}

BEHAVIOR_RESULT SetVelocityForKinematicOpposedDirTask::Run()
{
	DIRECTION eDirection = m_pGameObject.lock()->GetDirection();
	Vec3 vVelocity = m_vVelocity;
	vVelocity.x = fabs(vVelocity.x);
	vVelocity.x = eDirection != DIRECTION::LEFT ? -vVelocity.x : vVelocity.x;
	m_pGameObject.lock()->GetRigidBody()->SetVelocity(vVelocity);
	return BEHAVIOR_RESULT::SUCCESS;
}
