#pragma once
#include "MonoBehaviour.h"
class PlayerMoveScript :
    public MonoBehaviour
{
public:
    PlayerMoveScript();
    virtual ~PlayerMoveScript();

public:
    virtual void LateUpdate() override;

private:
    PlayerFilterShaders m_FilterShaders;
    float m_fSpeed;
    float m_fJumpSpeed;

    bool m_bPauseFlag;
    Timer m_tPauseTimer;
};

