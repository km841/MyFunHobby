#pragma once
#include "MonoBehaviour.h"
class Camera;
class CameraFadeInOutScript :
    public MonoBehaviour
{
public:
    CameraFadeInOutScript(shared_ptr<Camera> pCamera);
    virtual ~CameraFadeInOutScript();

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Camera> m_pCamera;

    float m_fAccTime;
    float m_fMaxTime;

    CAMERA_EFFECT m_ePrevCameraEffect;
};

