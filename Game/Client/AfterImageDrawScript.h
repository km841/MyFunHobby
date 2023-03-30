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
    TimeCounter      m_tcDuration;
};

