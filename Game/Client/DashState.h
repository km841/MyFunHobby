#pragma once
#include "PlayerState.h"

class AfterImage;
class DashState :
    public PlayerState
{
public:
    explicit DashState(shared_ptr<Player> pPlayer);
    virtual ~DashState() = default;

public:
    virtual void Update() override;

public:
    virtual void Enter() override;
    virtual void Exit()  override;

private:
    TimeCounter m_tcDuration;
    float m_fDashSpeed;

    std::vector<shared_ptr<AfterImage>> m_vAfterImages;
    int32 m_iAfterImageMaxCount;
};

