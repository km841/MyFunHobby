#pragma once
#include "BehaviorTask.h"
class ConditionToken;
class TokenStateChangeTask :
    public BehaviorTask
{
public:
    TokenStateChangeTask(shared_ptr<GameObject> pGameObject, shared_ptr<ConditionToken> pToken, bool bSetState);
    virtual ~TokenStateChangeTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    shared_ptr<ConditionToken> m_pToken;
    bool m_bState;
};

