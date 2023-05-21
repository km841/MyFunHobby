#pragma once
#include "BehaviorTask.h"
class Player;
class InfantryTackleTask :
    public BehaviorTask
{
public:
    InfantryTackleTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
    float m_fDistance;

    bool m_bInitDir;
    DIRECTION m_eDirection;
};

