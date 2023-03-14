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
    float m_fSpeed;

};

