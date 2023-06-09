#pragma once
#include "BehaviorTask.h"
class RunSpineAnimateTask :
    public BehaviorTask
{
public:
    RunSpineAnimateTask(shared_ptr<GameObject> pGameObject, const string& szAnimationName, bool bLoop = true);
    virtual BEHAVIOR_RESULT Run() override;

private:
    string m_szAnimationName;
    bool m_bLoop;
};

