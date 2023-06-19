#pragma once
#include "BehaviorTask.h"
class SetVelocityForKinematicOpposedDirTask :
    public BehaviorTask
{
public:
    SetVelocityForKinematicOpposedDirTask(shared_ptr<GameObject> pGameObject, const Vec3& vVelocity);
    virtual ~SetVelocityForKinematicOpposedDirTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    Vec3 m_vVelocity;
};

