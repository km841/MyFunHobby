#pragma once
#include "BehaviorTask.h"
class VelocityZeroForKinematicTask :
    public BehaviorTask
{
public:
    VelocityZeroForKinematicTask(shared_ptr<GameObject> pGameObject);
    virtual ~VelocityZeroForKinematicTask();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

