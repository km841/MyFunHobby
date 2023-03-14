#pragma once
#include "Object.h"

struct MassProperties
{
    MassProperties(float fStaticFriction = 0.5f, float fDynamicFriction = 0.2f, float fRestitution = 0.603f)
        : fStaticFriction(fStaticFriction)
        , fDynamicFriction(fDynamicFriction)
        , fRestitution(fRestitution)
    { }

    float fStaticFriction;
    float fDynamicFriction;
    float fRestitution;
};

class PhysicsProperties :
    public Object
{
public:
    PhysicsProperties(const MassProperties& massProperties);
    ~PhysicsProperties();

    void ApplyToShape(PxShape* pShape);
    void SetMaterialFlag(PxMaterialFlags eFlag) { m_pMaterial->setFlags(eFlag); }

public:
    virtual void Save(const wstring& szPath) override;
    virtual void Load(const wstring& szPath) override;

public:
    PxMaterial* GetMaterial() { return m_pMaterial; }

    float GetStaticFriction() { return m_fStaticFriction; }
    float GetDynamicFriction() { return m_fDynamicFriction; }
    float GetRestitution() { return m_fRestitution; }

    void SetStaticFriction(float fFriction);
    void SetDynamicFriction(float fFriction);
    void SetRestitution(float fRestitution);

private:
    float m_fStaticFriction;
    float m_fDynamicFriction;
    float m_fRestitution;

private:
    PxMaterial* m_pMaterial;
};

