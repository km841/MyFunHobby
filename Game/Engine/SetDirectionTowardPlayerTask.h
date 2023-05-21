#pragma once
#include "BehaviorTask.h"
class Player;
class SetDirectionTowardPlayerTask :
    public BehaviorTask
{
public:
    SetDirectionTowardPlayerTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;

};

