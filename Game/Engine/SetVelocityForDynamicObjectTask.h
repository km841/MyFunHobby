#pragma once
#include "BehaviorTask.h"
class SetVelocityForDynamicObjectTask :
    public BehaviorTask
{
public:
    SetVelocityForDynamicObjectTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity);
    virtual ~SetVelocityForDynamicObjectTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    Vec3 m_vVelocity;
};

