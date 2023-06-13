#pragma once
#include "BehaviorTask.h"
class ChangeChimeraRandomStateTask :
    public BehaviorTask
{
public:
    ChangeChimeraRandomStateTask(shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    bool m_bChecked;
};

