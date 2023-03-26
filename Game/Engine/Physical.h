#pragma once
#include "Component.h"
#include "PhysicsProperties.h"



class Physical :
    public Component
{
public:
    Physical(ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vGeometrySize, const MassProperties& massProperties = MassProperties());
    ~Physical();

public:
    virtual void Awake() override;

    virtual void Update() override;

public:
    PxController*          GetController()   { return m_pController; }
    PxActor*               GetActor()        { return m_pActor; }
    ACTOR_TYPE             GetActorType()    { return m_eActorType; }
    GEOMETRY_TYPE          GetGeometryType() { return m_eGeometryType; }
    PxShape*               GetShape()        { return m_pShape; }
    const Vec3&            GetGeometrySize() { return m_vSize; }

    shared_ptr<Geometries> GetGeometries()   { return m_pGeometries; }

private:
    void          CreateBoxGeometry(GEOMETRY_TYPE eGeometryType, const Vec3& vBoxSize);
    void          CreateCapsuleGeometry(GEOMETRY_TYPE eGeometryType, float fRadius, float fHalfHeight);
    void          CreatePlaneGeometry(GEOMETRY_TYPE eGeometryType);
    
private:
    void          CreatePhysicsProperties(const MassProperties& massProperties = MassProperties());
    void          CreateGeometry(GEOMETRY_TYPE eGeometryType, const Vec3& vShapeSize);
    void          CreateShape();
    void          CreateActor();
    void          InitializeActor();
    void          CreateController();
    void          AddActor(PxActor* pActor);
    void          ApplyShapeScale();

private:
    ACTOR_TYPE                    m_eActorType;
    GEOMETRY_TYPE                 m_eGeometryType;
                                                            
    Vec3                          m_vSize;
                                  
    PxActor*                      m_pActor;
    PxShape*                      m_pShape;
    PxController*                 m_pController;

    shared_ptr<PhysicsProperties> m_pProperties;
    shared_ptr<Geometries>        m_pGeometries;
};

