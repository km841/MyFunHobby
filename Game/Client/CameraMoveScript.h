#pragma once
#include "MonoBehaviour.h"
class CameraMoveScript :
    public MonoBehaviour
{
public:
    CameraMoveScript();
    virtual ~CameraMoveScript();


public:
    virtual void LateUpdate() override;


private:
    float m_fSpeed;
};

