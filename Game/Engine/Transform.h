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
    void SetLocalScale(const Vec3& vScale)       
    { 
        m_vLocalScale = vScale; 
        m_bChanged = true; 
    }

    FORCEINLINE void               SetLocalRotation(const Vec3& vRotation)       { m_vLocalRotation = vRotation; }
    FORCEINLINE void               SetLocalPosition(const Vec3& vPosition)       { m_vLocalTranslation = vPosition; }
                                                                                 
    FORCEINLINE void               SetLocalMatrix(const Matrix& matLocal)        { m_matLocal = matLocal; }
    FORCEINLINE Matrix             GetLocalMatrix() const                        { return m_matLocal; }        
                                                               
    FORCEINLINE const Vec3&        GetLocalPosition() const                      { return m_vLocalTranslation; }
    FORCEINLINE const Vec3&        GetLocalRotation() const                      { return m_vLocalRotation; }
    FORCEINLINE const Vec3&        GetLocalScale() const                         { return m_vLocalScale; }

    FORCEINLINE const Matrix&      GetLocalToWorldMatrix() const                 { return m_matWorld; }
    FORCEINLINE const Matrix&      GetPxLocalToWorldMatrix() const               { return m_matPxWorld; }
    FORCEINLINE const PxTransform& GetPxTransform() const                        { return m_PxTransform; }
    FORCEINLINE void              SetPxTransform(const PxTransform& pxTransform) { m_PxTransform = pxTransform; }

    FORCEINLINE void               SetGlobalOffset(const Vec2& vOffset)          { m_vGlobalOffset = vOffset; }
    FORCEINLINE const Vec2&        GetGlobalOffset()                             { return m_vGlobalOffset; }

    FORCEINLINE bool               IsChangedFlag() const                         { return m_bChanged; }
    FORCEINLINE void               ChangedFlagOff()                              { m_bChanged = false; }

    Vec3             GetRight() { return m_matWorld.Right(); }
    Vec3             GetUp()    { return m_matWorld.Up(); }
    Vec3             GetLook()  { return m_matWorld.Backward(); }

public:
    FORCEINLINE weak_ptr<Transform> GetParent()                            const { return m_pParent; }
    FORCEINLINE void                SetParent(shared_ptr<Transform> pParent)     { m_pParent = pParent; }

private:
    weak_ptr<Transform> m_pParent;

    Vec3    m_vLocalScale;
    Vec3    m_vLocalRotation;
    Vec3    m_vLocalTranslation;

    Matrix  m_matLocal = {};
    Matrix  m_matWorld = {};
    Matrix  m_matPxLocal = {};
    Matrix  m_matPxWorld = {};

    PxTransform m_PxTransform;

    PxVec3   m_vPxLocalScale;
    PxMat33  m_vPxLocalRotation;
    PxVec3   m_vPxLocalTranslation;

    Vec2     m_vGlobalOffset;

    bool m_bChanged;
};

