#include "pch.h"
#include "VelocityZeroForKinematicTask.h"
#include "RigidBody.h"

VelocityZeroForKinematicTask::VelocityZeroForKinematicTask(shared_ptr<GameObject> pGameObject)
    : BehaviorTask(pGameObject)
{
}

VelocityZeroForKinematicTask::~VelocityZeroForKinematicTask()
{
}

BEHAVIOR_RESULT VelocityZeroForKinematicTask::Run()
{
    m_pGameObject.lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
    return BEHAVIOR_RESULT::SUCCESS;
}
