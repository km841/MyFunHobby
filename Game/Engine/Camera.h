#pragma once
#include "Component.h"
#include "Frustum.h"

enum class PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC,
};

class Camera :
       public Component
     , public std::enable_shared_from_this<Camera>
{
public:
    Camera();
    virtual ~Camera();

    virtual void    Update() override;
    virtual void    FinalUpdate() override;

    FORCEINLINE void             SetProjectionType(PROJECTION_TYPE eType)     { m_eType = eType; }
    FORCEINLINE PROJECTION_TYPE  GetProjectionType()   const                  { return m_eType; }

    FORCEINLINE const Matrix&    GetOldViewMatrix()    const                  { return m_matOldView; }
    FORCEINLINE const Matrix&    GetViewMatrix()       const                  { return m_matView; }
    FORCEINLINE const Matrix&    GetProjectionMatrix() const                  { return m_matProjection; }
    
    void            SortGameObject();
    void            SetCullingMask(LAYER_TYPE eLayerType, bool bFlag);
    void            DisableAllCullingMask();
    void            EnableAllCullingMask();
    bool            ContainsSphere(const Vec3& vPos, float fRadius)           { return m_Frustum.ContainsSphere(vPos, fRadius); }

    void SetCameraSpeed(const Vec3& vCameraSpeed) { m_vCameraSpeed = vCameraSpeed; }
    const Vec3& GetCameraSpeed() { return m_vCameraSpeed; }
    void SetLimitRect(const Vec4& vLimitRect);
    

    const Vec4& GetLimitRect() { return m_vLimitRect; }

    void SetTargetPos(const Vec3& vPos, float fTime);
    void SetFixedCamera(const Vec3& vFixedPos) { m_bFixedCamera = true; m_vFixedPos = vFixedPos; }
    void UnfixCamera() { m_bFixedCamera = false;}
    bool IsFixed() { return m_bFixedCamera; }
    const Vec3& GetFixedPosition() { return m_vFixedPos; }

    void DisableTracking() { m_bTrackingUnused = true; }
    void EnableTracking() { m_bTrackingUnused = false; }
    bool IsTrackingUnused() { return m_bTrackingUnused; }

    FORCEINLINE void FlipDebugMode() { m_bDebugMode = (m_bDebugMode + 1) % 2; }

public:
    void Render_Forward();
    void Render_Deferred();

private:
    PROJECTION_TYPE m_eType;

    float           m_fNear;
    float           m_fFar;
    float           m_fFov;
    float           m_fScale;

    Matrix          m_matOldView;
    Matrix          m_matView;
    Matrix          m_matProjection;

    uint32          m_iCullingMask;

    Frustum         m_Frustum;

    Vec3            m_vCameraSpeed;
    Vec4            m_vLimitRect;

    bool            m_bDebugMode;
    bool            m_bFixedCamera;
    Vec3            m_vFixedPos;

    bool            m_bTrackingUnused;

    Vec3            m_vTargetPos;
    Vec3            m_vInitDir;
    Timer           m_tTrackingTimer;
    float           m_fTrackingSpeed;

    std::vector<shared_ptr<GameObject>> m_vForwardObjects;
    std::vector<shared_ptr<GameObject>> m_vDeferredObjects;
    std::vector<shared_ptr<GameObject>> m_vParticleObjects;

};

