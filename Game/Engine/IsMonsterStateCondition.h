#pragma once
#include "BehaviorCondition.h"

class IsMonsterStateCondition :
    public BehaviorCondition
{
public:
    IsMonsterStateCondition(shared_ptr<GameObject> pGameObject, MONSTER_STATE eMonsterState);
    virtual ~IsMonsterStateCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    MONSTER_STATE m_eMonsterState;
};

