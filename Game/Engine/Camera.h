#pragma once
#include "Component.h"

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

    virtual void    FinalUpdate() override;
    void            Render();

    FORCEINLINE void             SetProjectionType(PROJECTION_TYPE eType)     { m_eType = eType; }
    FORCEINLINE PROJECTION_TYPE  GetProjectionType()   const                  { return m_eType; }

    FORCEINLINE const Matrix&    GetViewMatrix()       const                  { return m_matView; }
    FORCEINLINE const Matrix&    GetProjectionMatrix() const                  { return m_matProjection; }

    FORCEINLINE CAMERA_EFFECT    GetCameraEffect()     const                  { return m_eCameraEffect; }
    FORCEINLINE void             SetCameraEffect(CAMERA_EFFECT eCameraEffect) { m_eCameraEffect = eCameraEffect; }
    FORCEINLINE void             RemoveCameraEffect() { m_eCameraEffect = CAMERA_EFFECT::NONE; }
    
    void            SetCullingMask(LAYER_TYPE eLayerType, bool bFlag);
    void            DisableAllCullingMask();
    void            EnableAllCullingMask();

private:
    PROJECTION_TYPE m_eType;

    float           m_fNear;
    float           m_fFar;
    float           m_fFov;
    float           m_fScale;

    Matrix          m_matView;
    Matrix          m_matProjection;

    uint32          m_iCullingMask;

    CAMERA_EFFECT   m_eCameraEffect;
};

