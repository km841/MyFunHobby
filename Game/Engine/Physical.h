#pragma once
#include "Component.h"
#include "PhysicsProperties.h"



class Physical :
    public Component
{
public:
    explicit Physical(ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vGeometrySize, const MassProperties& massProperties = MassProperties());
    ~Physical();

public:
    virtual void Awake() override;
    virtual void Update() override;

public:
    FORCEINLINE PxController*          GetController()   const { return m_pController; }
    FORCEINLINE ACTOR_TYPE             GetActorType()    const { return m_eActorType; }
    FORCEINLINE GEOMETRY_TYPE          GetGeometryType() const { return m_eGeometryType; }
    FORCEINLINE PxShape*               GetShape()        const { return m_pShape; }
    FORCEINLINE const Vec3&            GetGeometrySize() const { return m_vSize; }
    FORCEINLINE shared_ptr<Geometries> GetGeometries()   const { return m_pGeometries; }

    template<typename T>
    T* GetActor() const 
    { 
        T* pActor = m_pActor->is<T>();
        assert(pActor);
        return pActor;
    }

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

