#include "pch.h"
#include "SetVelocityForDynamicObjectTask.h"
#include "RigidBody.h"

SetVelocityForDynamicObjectTask::SetVelocityForDynamicObjectTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity)
    : BehaviorTask(pGameObject)
    , m_vVelocity(vVelocity)
{
}

SetVelocityForDynamicObjectTask::~SetVelocityForDynamicObjectTask()
{
}

BEHAVIOR_RESULT SetVelocityForDynamicObjectTask::Run()
{
    m_pGameObject.lock()->GetRigidBody()->SetLinearVelocityForDynamic(Conv::Vec3ToPxVec3(m_vVelocity));
    return BEHAVIOR_RESULT::SUCCESS;
}
