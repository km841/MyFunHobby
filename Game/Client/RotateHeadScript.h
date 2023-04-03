#pragma once
#include "MonoBehaviour.h"
class PlayerProjectile;
class RotateHeadScript :
    public MonoBehaviour
{
public:
    RotateHeadScript(weak_ptr<PlayerProjectile> pProjectile);
    virtual ~RotateHeadScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<PlayerProjectile> m_pProjectile;
    float m_fAngularSpeed;
    float m_fAccAngular;
};

