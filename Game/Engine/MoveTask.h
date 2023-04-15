#pragma once
#include "BehaviorTask.h"
class GameObject;
class MoveTask :
    public BehaviorTask
{
public:
    MoveTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    Timer m_tDuration;

};

