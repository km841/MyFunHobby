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
    , m_fScale(1.f)

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
        m_matProjection = XMMatrixOrthographicLH(fWidth, fHeight, m_fNear, m_fFar);
    }
}

void Camera::Render()
{
    shared_ptr<Scene> pCurScene = GET_SINGLE(Scenes)->GetActiveScene();
    const std::vector<shared_ptr<GameObject>>& vGameObjects = pCurScene->GetGameObjects();

    for (const shared_ptr<GameObject>& pGameObject : vGameObjects)
    {
        if (pGameObject->GetMeshRenderer())
        {
            if (pGameObject->IsEnable())
                pGameObject->GetMeshRenderer()->Render(shared_from_this());


            if (pGameObject->GetDebugRenderer())
            {
                pGameObject->GetDebugRenderer()->Render(shared_from_this());
            }
        }
    }
}
