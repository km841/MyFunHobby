#pragma once
#include "BehaviorTask.h"
class RunAnimateTask :
    public BehaviorTask
{
public:
    RunAnimateTask(shared_ptr<GameObject> pGameObject, const wstring& szAnimationName, bool bLoop = true, uint32 iSection = 0);
    virtual BEHAVIOR_RESULT Run() override;

private:
    wstring m_szAnimationName;
    bool m_bLoop;
    uint32 m_iSection;
};

