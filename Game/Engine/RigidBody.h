#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
public:
    RigidBody(bool bGravityApplied = false);
    virtual ~RigidBody();

    virtual void Awake() override;
    virtual void FinalUpdate() override;

public:
    bool        IsGravityApplied()                 { return m_bGravityApplied;   }
    void        ApplyGravity()                     { m_bGravityApplied = true;   }
    void        RemoveGravity()                    { m_bGravityApplied = false;  }

    const Vec3& GetGravityAccel()                  { return m_vGravityAccel;     }

    const Vec3& GetVelocity()                      { return m_vVelocity;         }
    void        AddVelocity(const Vec3& vVelocity) { m_vVelocity += vVelocity;   }
    void        SetVelocity(const Vec3& vVelocity) { m_vVelocity = vVelocity;    }
    void        SetVelocity(AXIS eAxis, float fVelocity);

    void        SetMass(float fMass)               { m_fMass = fMass; }
    float       GetMass()                          { return m_fMass;  }

private:
    void        Move();

private:
    bool m_bGravityApplied;
    Vec3 m_vGravityAccel;
    Vec3 m_vVelocity;

    float m_fMass;
};

