#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
public:
    explicit RigidBody(bool bGravityApplied = false);
    virtual ~RigidBody();

    virtual void Awake() override;
    virtual void FinalUpdate() override;

public:
    FORCEINLINE bool        IsGravityApplied() const           { return m_bGravityApplied;   }
    FORCEINLINE const Vec3& GetGravityAccel()  const           { return m_vGravityAccel;     }
    FORCEINLINE const Vec3& GetVelocity() const                { return m_vVelocity;         }
    FORCEINLINE float       GetMass() const                    { return m_fMass;  }

    FORCEINLINE void        ApplyGravity()                     { m_bGravityApplied = true;   }
    FORCEINLINE void        RemoveGravity()                    { m_bGravityApplied = false;  }
    FORCEINLINE void        AddVelocity(const Vec3& vVelocity) { m_vVelocity += vVelocity;   }
    FORCEINLINE void        SetVelocity(const Vec3& vVelocity) { m_vVelocity = vVelocity;    }
    FORCEINLINE void        SetMass(float fMass)               { m_fMass = fMass; }
    
public:
    float                   GetVelocity(AXIS eAxis);
    void                    SetVelocity(AXIS eAxis, float fVelocity);
    void                    AddVelocity(AXIS eAxis, float fVelocity);

private:
    void        Move();

private:
    bool m_bGravityApplied;
    Vec3 m_vGravityAccel;
    Vec3 m_vVelocity;

    float m_fMass;
};

