#pragma once
#include "Component.h"

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

    void OnCollisionEnter(shared_ptr<Collider> pOtherCollider);
    void OnCollisionExit(shared_ptr<Collider> pOtherCollider);

    void OnTriggerEnter(shared_ptr<Collider> pOtherCollider);
    void OnTriggerStay(shared_ptr<Collider> pOtherCollider);
    void OnTriggerExit(shared_ptr<Collider> pOtherCollider);

public:
    FORCEINLINE const PxRaycastHit& GetRaycastHit() const { return m_RaycastHit; }
    FORCEINLINE const PxSweepHit&   GetSweepHit()   const { return m_SweepHit;   }
    FORCEINLINE const PxOverlapHit& GetOverlapHit() const { return m_OverlapHit; }
    FORCEINLINE PxFilterData&       GetFilterData()       { return m_FilterData; }

    bool                            Raycast(const Vec3& vOrigin, const Vec3& vDir, shared_ptr<GameObject> pGameObject, float fMaxDistance);
    bool                            Overlap(const PxGeometry& otherGeom, const PxTransform& otherTransform);
    bool                            Sweep(const PxGeometry& otherGeom, const PxTransform& otherTransform);
    Vec3                            ComputePenetration(shared_ptr<GameObject> pGameObject);


private:
    void CreateDebugGeometry(shared_ptr<Geometries> pGeometries);
    void CreateDebugBox(const Vec3& vHalfSize);

private:
    PxRaycastHit     m_RaycastHit;
    PxSweepHit       m_SweepHit;
    PxOverlapHit     m_OverlapHit;
    PxFilterData     m_FilterData;

    float  m_fMaxDist;
    uint32 m_fRaycastMaxHit;

    PxVec3   m_vPenetDir;
    float  m_fPenetDepth;
};

