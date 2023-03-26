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

    void            SetProjectionType(PROJECTION_TYPE eType) { m_eType = eType; }
    PROJECTION_TYPE GetProjectionType() { return m_eType; }

    const Matrix&   GetViewMatrix() { return m_matView; }
    const Matrix&   GetProjectionMatrix() { return m_matProjection; }

    void            Render();

    void            SetCameraEffect(CAMERA_EFFECT eCameraEffect) { m_eCameraEffect = eCameraEffect; }
    CAMERA_EFFECT   GetCameraEffect() { return m_eCameraEffect; }
    void            RemoveCameraEffect() { m_eCameraEffect = CAMERA_EFFECT::NONE; }
    
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

