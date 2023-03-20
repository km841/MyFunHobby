#pragma once
#include "Component.h"

class ContactCallback;
using RaycastResult = std::pair<bool, Vec3>;
class Collider :
      public Component
{
public:
    Collider();
    virtual ~Collider();
public:
    virtual void Awake() override;
    virtual void FinalUpdate() override;
    virtual void Render() override;

    virtual void OnCollision();

public:
    const PxRaycastHit& GetRaycastHit() { return m_RaycastHit; }
    const PxSweepHit&   GetSweepHit()   { return m_SweepHit; }
    RaycastResult       Raycast(Vec3 vOrigin, Vec3 vDir);

private:
    void CreateDebugGeometry(shared_ptr<Geometries> pGeometries);
    void CreateDebugBox(Vec3 vHalfSize);
    void CreateDebugCapsule(float fRadius, float fHalfHeight);

private:
    ContactCallback* m_pCallback;
    PxRaycastHit     m_RaycastHit;
    PxSweepHit       m_SweepHit;
    PxOverlapHit     m_OverlapHit;

    float m_fRaycastMaxDist;
    uint32 m_fRaycastMaxHit;
};

