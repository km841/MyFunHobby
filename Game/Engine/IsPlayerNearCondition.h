#pragma once
#include "BehaviorCondition.h"
class Player;
class Monster;
class IsPlayerNearCondition :
    public BehaviorCondition
{
public:
    IsPlayerNearCondition(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual ~IsPlayerNearCondition();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
};

