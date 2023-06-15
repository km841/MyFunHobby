#pragma once
#include "BehaviorTask.h"
class RemoveToSceneTask :
    public BehaviorTask
{
public:
    RemoveToSceneTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
};

