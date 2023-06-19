#pragma once
#include "BehaviorTask.h"
class SetVelocityForKinematicObjectTask :
    public BehaviorTask
{
public:
    SetVelocityForKinematicObjectTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity);
    virtual ~SetVelocityForKinematicObjectTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    Vec3 m_vVelocity;
};

