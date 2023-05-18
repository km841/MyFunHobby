#pragma once
#include "BehaviorTask.h"
class Player;
class TrackingOfMeleeTask :
    public BehaviorTask
{
public:
    TrackingOfMeleeTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject);
    virtual ~TrackingOfMeleeTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
};

