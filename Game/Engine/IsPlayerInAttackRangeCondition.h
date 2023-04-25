#pragma once
#include "BehaviorCondition.h"
class Player;
class IsPlayerInAttackRangeCondition :
    public BehaviorCondition
{
public:
    IsPlayerInAttackRangeCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual ~IsPlayerInAttackRangeCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
};

