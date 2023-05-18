#pragma once
#include "BehaviorTask.h"
class Player;
class KnightAttackTask :
    public BehaviorTask
{
public:
    KnightAttackTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
    float m_fSlidingRange;
    float m_fSlidingSpeed;
};

