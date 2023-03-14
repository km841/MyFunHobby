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
       
public:
    void SetLocalScale(const Vec3& vScale)       
    { 
        m_vLocalScale = vScale; 
        m_bChanged = true; 
    }

    void          SetLocalRotation(const Vec3& vRotation) { m_vLocalRotation = vRotation; }
    void          SetLocalPosition(const Vec3& vPosition) { m_vLocalTranslation = vPosition; }
                  
    void          SetLocalMatrix(const Matrix& matLocal)  { m_matLocal = matLocal; }
    Matrix        GetLocalMatrix()                        { return m_matLocal; }
                  
    void          SetPxTransform(PxTransform& pxTrans)    { m_PxTransform = pxTrans; }
                  
                  
    Vec3          GetRight()              { return m_matWorld.Right(); }
    Vec3          GetUp()                 { return m_matWorld.Up(); }
    Vec3          GetLook()               { return m_matWorld.Backward(); }
                  
    const Vec3&   GetLocalPosition()      { return m_vLocalTranslation; }
    const Vec3&   GetLocalRotation()      { return m_vLocalRotation; }
    const Vec3&   GetLocalScale()         { return m_vLocalScale; }

    const Matrix& GetLocalToWorldMatrix() { return m_matWorld; }




    bool IsChangedFlag()  { return m_bChanged; }
    void ChangedFlagOff() { m_bChanged = false; }


private:
    Vec3    m_vLocalScale;
    Vec3    m_vLocalRotation;
    Vec3    m_vLocalTranslation;

    Matrix  m_matLocal = {};
    Matrix  m_matWorld = {};

    PxTransform m_PxTransform;

    bool m_bChanged;
};

