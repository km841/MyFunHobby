#pragma once
#include "MonoBehaviour.h"
class Player;
class AfterImageDrawScript :
    public MonoBehaviour
{
public:
    explicit AfterImageDrawScript(shared_ptr<Player> pPlayer);
    virtual ~AfterImageDrawScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Player> m_pPlayer;
    Timer            m_tDuration;

    bool             m_bTrigger;
};

