#pragma once
#include "MonoBehaviour.h"
class Camera;
class FadeInOutScript :
    public MonoBehaviour
{
public:
    FadeInOutScript(shared_ptr<Camera> pCamera);
    virtual ~FadeInOutScript();

public:

public:
    virtual void LateUpdate() override;

private:
    weak_ptr<Camera> m_pCamera;

    float m_fAccTime;
    float m_fMaxTime;

    CAMERA_EFFECT m_ePrevCameraEffect;
};

