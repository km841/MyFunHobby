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
    // for kinematic actors
    FORCEINLINE bool        IsAccelerating() const             { return fabs(m_vVelocity.Length()) > 0.f; }
    FORCEINLINE bool        IsGravityApplied() const           { return m_bGravityApplied;   }
    FORCEINLINE const Vec3& GetGravityAccel()  const           { return m_vGravityAccel;     }
    FORCEINLINE const Vec3& GetVelocity() const                { return m_vVelocity;         }
    FORCEINLINE void        ApplyGravity()                     { m_bGravityApplied = true;   }
    FORCEINLINE void        RemoveGravity()                    { m_bGravityApplied = false;  }
    FORCEINLINE void        AddVelocity(const Vec3& vVelocity) { m_vVelocity += vVelocity;   }
    FORCEINLINE void        SetVelocity(const Vec3& vVelocity) { m_vVelocity = vVelocity;    }


public:
    // for kinematic actors
    float GetVelocity(AXIS eAxis);
    void  SetVelocity(AXIS eAxis, float fVelocity);
    void  AddVelocity(AXIS eAxis, float fVelocity);
    void  ReserveSpeedForSeconds(const Vec3& vVelocity, float fDuration);

public:
    // for dynamic actors
    void SetMassForDynamic(float fMass);
    void SetLinearVelocityForDynamic(const PxVec3& vLinearVelocity);
    void SetLinearVelocityForDynamic(AXIS eAxis, float fVelocity);
    void SetAngularVelocityForDynamic(const PxVec3& vAngularVelocity);
    void AddForceForDynamic(const PxVec3& vForce, PxForceMode::Enum eForceMode);
    void SetLinearDamping(float fDamping);
    void SetAngularDamping(float fDamping);
    void SetLinearMaxVelocityForDynamic(float fMaxVelocity);
    void SetAngularMaxVelocityForDynamic(float fMaxVelocity);
    void ApplyGravityForDynamic();
    void RemoveGravityForDynamic();
    void SetRotationZForDynamic(float fRotationZ);

private:
    bool m_bGravityApplied;
    Vec3 m_vGravityAccel;
    Vec3 m_vVelocity;
    Vec3 m_vMaxVelocity;

    Vec3 m_vReserveVelocity;
    Timer m_tReserveTimer;
};

