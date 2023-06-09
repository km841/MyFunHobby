#pragma once
#include "BehaviorTask.h"
class Player;
class SetVelocityGoToPlayerPosTask :
    public BehaviorTask
{
public:
    SetVelocityGoToPlayerPosTask(shared_ptr<Player> pPlayer, shared_ptr<GameObject> pGameObject, const Vec3& vVelocity);
    virtual ~SetVelocityGoToPlayerPosTask();

public:
    virtual BEHAVIOR_RESULT Run() override;

private:
    weak_ptr<Player> m_pPlayer;
    Vec3 m_vVelocity;
};

