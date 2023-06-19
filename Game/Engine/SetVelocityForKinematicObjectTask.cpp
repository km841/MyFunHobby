#include "pch.h"
#include "SetVelocityForKinematicObjectTask.h"
#include "RigidBody.h"

SetVelocityForKinematicObjectTask::SetVelocityForKinematicObjectTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity)
	: BehaviorTask(pGameObject)
	, m_vVelocity(vVelocity)
{
}

SetVelocityForKinematicObjectTask::~SetVelocityForKinematicObjectTask()
{
}

BEHAVIOR_RESULT SetVelocityForKinematicObjectTask::Run()
{
	m_pGameObject.lock()->GetRigidBody()->SetVelocity(m_vVelocity);
	return BEHAVIOR_RESULT::SUCCESS;
}
