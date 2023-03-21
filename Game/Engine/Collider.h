#pragma once
#include "Component.h"

class ContactCallback;
class Collider :
      public Component
{
public:
    Collider();
    virtual ~Collider();

public:
    virtual void Awake() override;
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render() override;

    virtual void OnCollision();

public:
    const PxRaycastHit& GetRaycastHit() { return m_RaycastHit; }
    const PxSweepHit&   GetSweepHit()   { return m_SweepHit;   }
    const PxOverlapHit& GetOverlapHit() { return m_OverlapHit; }
    PxFilterData&       GetFilterData() { return m_FilterData; }
    RaycastResult       Raycast(Vec3 vOrigin, Vec3 vDir);
    bool                Overlap(const PxGeometry& otherGeom, const PxTransform& otherTransform);

private:
    void CreateDebugGeometry(shared_ptr<Geometries> pGeometries);
    void CreateDebugBox(Vec3 vHalfSize);
    void CreateDebugCapsule(float fRadius, float fHalfHeight);

private:
    ContactCallback* m_pCallback;
    PxRaycastHit     m_RaycastHit;
    PxSweepHit       m_SweepHit;
    PxOverlapHit     m_OverlapHit;
    PxFilterData     m_FilterData;

    float  m_fRaycastMaxDist;
    uint32 m_fRaycastMaxHit;
};

