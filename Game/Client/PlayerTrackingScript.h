#pragma once
#include "MonoBehaviour.h"

class Player;
class PlayerTrackingScript :
    public MonoBehaviour
{
public:
    PlayerTrackingScript(shared_ptr<Player> pPlayer);
    virtual ~PlayerTrackingScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
};

