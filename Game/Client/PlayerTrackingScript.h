#pragma once
#include "MonoBehaviour.h"

class Player;
class PlayerTrackingScript :
    public MonoBehaviour
{
public:
    explicit PlayerTrackingScript(shared_ptr<Player> pPlayer, float fDepth = 1.f);
    virtual ~PlayerTrackingScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
    float m_fDepth;
};

