#pragma once
#include "MonoBehaviour.h"
class Player;
class ObjectFollowScript :
    public MonoBehaviour
{
public:
    ObjectFollowScript(shared_ptr<Player> pPlayer);
    virtual ~ObjectFollowScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

