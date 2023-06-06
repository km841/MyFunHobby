#pragma once
#include "Component.h"

class Camera;
class Transform :
    public Component
{
public:
    Transform();
    virtual ~Transform();

public:
    virtual void  Awake() override;
    virtual void  FinalUpdate() override;

public:           
    void          PushData(shared_ptr<Camera> pCamera);
    void          PxPushData(shared_ptr<Camera> pCamera);
       
public:
    FORCEINLINE void               SetLocalScale(const Vec3& vScale)             { m_vLocalScale = vScale; }
    FORCEINLINE void               SetLocalRotation(const Vec3& vRotation)       { m_vLocalRotation = vRotation; }
    FORCEINLINE void               SetLocalPosition(const Vec3& vPosition)       { m_vLocalTranslation = vPosition; }
                                                                                 
    FORCEINLINE void               SetLocalMatrix(const Matrix& matLocal)        { m_matLocal = matLocal; }
    FORCEINLINE Matrix             GetLocalMatrix() const                        { return m_matLocal; }        
                                                               
    FORCEINLINE const Vec3&        GetLocalPosition() const                      { return m_vLocalTranslation; }
    FORCEINLINE const Vec3&        GetLocalRotation() const                      { return m_vLocalRotation; }
    FORCEINLINE const Vec3&        GetLocalScale() const                         { return m_vLocalScale; }

    FORCEINLINE const Matrix&      GetLocalToWorldMatrix() const                 { return m_matWorld; }
    FORCEINLINE const Matrix&      GetLocalToWorldOldMatrix() const              { return m_matOldWorld; }

    FORCEINLINE const Matrix&      GetPxLocalToWorldMatrix() const               { return m_matPxWorld; }
    FORCEINLINE const PxTransform& GetPxTransform() const                        { return m_PxTransform; }
    FORCEINLINE void               SetPxTransform(const PxTransform& pxTransform) { m_PxTransform = pxTransform; }

    FORCEINLINE void               SetGlobalOffset(const Vec2& vOffset)          { m_vGlobalOffset = vOffset; }
    FORCEINLINE const Vec2&        GetGlobalOffset()                             { return m_vGlobalOffset; }

    FORCEINLINE float              GetBoundingSphereRadius()                     { return std::max(std::max(m_vLocalScale.x, m_vLocalScale.y), m_vLocalScale.z); }

   

    Vec3 GetRight() { return m_matWorld.Right(); }
    Vec3 GetUp()    { return m_matWorld.Up(); }
    Vec3 GetLook()  { return m_matWorld.Backward(); }

    Vec3 GetWorldPosition();
    void SetPhysicalPosition(const Vec3& vPosition);
    Vec3 GetPhysicalPosition();

public:
    FORCEINLINE weak_ptr<Transform> GetParent() const                            { return m_pParent; }
    FORCEINLINE void                SetParent(shared_ptr<Transform> pParent)     { m_pParent = pParent; }

private:
    weak_ptr<Transform> m_pParent;

    Vec3    m_vLocalScale;
    Vec3    m_vLocalRotation;
    Vec3    m_vLocalTranslation;

    Matrix  m_matLocal = {};
    Matrix  m_matWorld = {};
    Matrix  m_matOldWorld = {};
    Matrix  m_matPxWorld = {};

    PxTransform m_PxTransform;
    Vec2     m_vGlobalOffset;
};

