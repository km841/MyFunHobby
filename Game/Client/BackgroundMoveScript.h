#pragma once
#include "MonoBehaviour.h"
class BackgroundMoveScript :
    public MonoBehaviour
{
public:
    BackgroundMoveScript(float fSpeed);
    virtual ~BackgroundMoveScript();

public:
    virtual void LateUpdate() override;

private:
    float m_fSpeed;
};

