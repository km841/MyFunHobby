#pragma once
#include "MonoBehaviour.h"
class PlayerProjectile;
class Possession;
class RotateHeadScript :
    public MonoBehaviour
{
public:
    RotateHeadScript(weak_ptr<Possession> pProjectile);
    virtual ~RotateHeadScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Possession> m_pProjectile;
    float m_fAngularSpeed;
    float m_fAccAngular;
};

