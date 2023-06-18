#pragma once
#include "BehaviorCondition.h"
class ConditionToken;
class IsTokenStateCondition :
    public BehaviorCondition
{
public:
    IsTokenStateCondition(shared_ptr<GameObject> pGameObject, shared_ptr<ConditionToken> pToken, bool bSelectState);
    virtual ~IsTokenStateCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    shared_ptr<ConditionToken> m_pToken;
    bool m_bState;
};

