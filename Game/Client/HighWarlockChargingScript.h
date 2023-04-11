#pragma once
#include "MonoBehaviour.h"
class HighWarlock;
class HighWarlockChargingScript :
    public MonoBehaviour
{
public:
    explicit HighWarlockChargingScript(shared_ptr<HighWarlock> pHighWarlock);
    virtual ~HighWarlockChargingScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<HighWarlock> m_pHighWarlock;
    PLAYER_STATE m_eRealTimePlayerState;
    bool m_bChargedFlag;
    bool m_bCompleteFlag;

};

