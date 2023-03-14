#pragma once
#include "MonoBehaviour.h"
class Camera;
class GridDrawScript :
    public MonoBehaviour
{
public:
    GridDrawScript(shared_ptr<Camera> pCamera);
    virtual ~GridDrawScript();

public:
    virtual void LateUpdate() override;

private:
    shared_ptr<Camera> m_pCamera;
    Vec2  m_vGridOffset;
    float m_fThickness;
};

