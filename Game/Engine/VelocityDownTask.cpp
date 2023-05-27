#include "pch.h"
#include "VelocityDownTask.h"
#include "RigidBody.h"

VelocityDownTask::VelocityDownTask(shared_ptr<GameObject> pGameObject)
	: BehaviorTask(pGameObject)
{
}

VelocityDownTask::~VelocityDownTask()
{
}

BEHAVIOR_RESULT VelocityDownTask::Run()
{
	m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
	return BEHAVIOR_RESULT::SUCCESS;
}
