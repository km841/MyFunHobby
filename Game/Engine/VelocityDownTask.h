#pragma once
#include "BehaviorTask.h"
class VelocityDownTask :
    public BehaviorTask
{
public:
    VelocityDownTask(shared_ptr<GameObject> pGameObject);
    virtual ~VelocityDownTask();

public:
    virtual BEHAVIOR_RESULT Run() override;
};

