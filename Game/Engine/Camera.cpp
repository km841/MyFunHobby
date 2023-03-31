#include "pch.h"
#include "Engine.h"
#include "Camera.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "DebugRenderer.h"

Camera::Camera()
	:Component(COMPONENT_TYPE::CAMERA)
    , m_eType(PROJECTION_TYPE::ORTHOGRAPHIC)
    , m_fNear(1.f)
    , m_fFar(1000.f)
    , m_fFov(XM_PI / 4.f)
    , m_fScale(1.25f)
    , m_eCameraEffect(CAMERA_EFFECT::NONE)
    , m_iCullingMask(0)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
    shared_ptr<Transform> pTransform = GetTransform();
    Matrix matWorld = pTransform->GetLocalToWorldMatrix();

    // Scale값이 1이여야 값이 제대로 나온다.
    Matrix matWorldInv = matWorld.Invert();
    m_matView = matWorldInv;

    float fWidth = static_cast<float>(g_pEngine->GetWidth());
    float fHeight = static_cast<float>(g_pEngine->GetHeight());

    if (PROJECTION_TYPE::PERSPECTIVE == m_eType)
    {
        m_matProjection = XMMatrixPerspectiveFovLH(m_fFov, fWidth / fHeight, m_fNear, m_fFar);
    }
    else
    {
        m_matProjection = XMMatrixOrthographicLH(fWidth / m_fScale, fHeight / m_fScale, m_fNear, m_fFar);
    }
}

void Camera::Render()
{
    shared_ptr<Scene> pCurScene = GET_SINGLE(Scenes)->GetActiveScene();

    for (int32 i = 0; i < LAYER_TYPE_COUNT; ++i)
    {
        if (m_iCullingMask & (1 << i))
            continue;

        const std::vector<shared_ptr<GameObject>>& vGameObjects = pCurScene->GetGameObjects(static_cast<LAYER_TYPE>(i));
        for (const shared_ptr<GameObject>& pGameObject : vGameObjects)
        {
            if (pGameObject->IsEnable())
            {
                if (pGameObject->GetMeshRenderer())
                    pGameObject->GetMeshRenderer()->Render(shared_from_this());

                if (pGameObject->GetDebugRenderer())
                    pGameObject->GetDebugRenderer()->Render(shared_from_this());
            }
        }
    }


}

void Camera::SetCullingMask(LAYER_TYPE eLayerType, bool bFlag)
{
    if (bFlag)
        m_iCullingMask |= 1 << static_cast<uint8>(eLayerType);
    else
        m_iCullingMask &= ~(1 << static_cast<uint8>(eLayerType));
}

void Camera::DisableAllCullingMask()
{
    m_iCullingMask = 0;
}

void Camera::EnableAllCullingMask()
{
    for (int32 i = 0; i < LAYER_TYPE_COUNT - 1; ++i)
    {
        m_iCullingMask |= 1 << i;
    }
}
