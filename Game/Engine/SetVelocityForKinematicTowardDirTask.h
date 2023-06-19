#pragma once
#include "BehaviorTask.h"
class SetVelocityForKinematicTowardDirTask :
    public BehaviorTask
{
public:
    SetVelocityForKinematicTowardDirTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity);
    virtual ~SetVelocityForKinematicTowardDirTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    Vec3 m_vVelocity;
};

