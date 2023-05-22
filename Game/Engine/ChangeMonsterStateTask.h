#pragma once
#include "BehaviorTask.h"
class ChangeMonsterStateTask :
    public BehaviorTask
{
public:
    ChangeMonsterStateTask(shared_ptr<GameObject> pGameObject, MONSTER_STATE eMonsterState, bool bCondition = false);
    virtual BEHAVIOR_RESULT Run() override;

private:
    MONSTER_STATE m_eMonsterState;
    bool m_bCondition;
};

