#include "pch.h"
#include "Engine.h"
#include "Camera.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "DebugRenderer.h"
#include "Player.h"
#include "Skul.h"
#include "Material.h"
#include "Shader.h"
#include "ParticleSystem.h"
#include "Resources.h"
#include "Animator.h"
#include "Clock.h"

Camera::Camera()
	:Component(COMPONENT_TYPE::CAMERA)
    , m_eType(PROJECTION_TYPE::ORTHOGRAPHIC)
    , m_fNear(1.f)
    , m_fFar(3000.f)
    , m_fFov(XM_PI / 4.f)
    , m_fScale(1.25f)
    , m_iCullingMask(0)
    , m_bDebugMode(false)
    , m_bFixedCamera(false)
    , m_tTrackingTimer(0.f)
    , m_fTrackingSpeed(0.f)
    , m_bTrackingUnused(false)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
    if (m_tTrackingTimer.IsRunning())
    {
        m_tTrackingTimer.Update(WORLD_DELTA_TIME);

        Vec3 vMyPos = GetTransform()->GetLocalPosition();
        GetTransform()->SetLocalPosition(vMyPos + m_vInitDir * m_fTrackingSpeed * WORLD_DELTA_TIME);

        if (m_tTrackingTimer.IsFinished())
        {
            m_vTargetPos = Vec3::Zero;
            m_vInitDir = Vec3::Zero;
            m_fTrackingSpeed = 0.f;
            m_tTrackingTimer.Stop();
        }
    }
}

void Camera::FinalUpdate()
{
    shared_ptr<Transform> pTransform = GetTransform();
    Matrix matWorld = pTransform->GetLocalToWorldMatrix();
    Matrix matWorldInv = matWorld.Invert();

    // Old View Matrix
    m_matView = matWorldInv;
    m_matOldView = m_matView;

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

    m_Frustum.FinalUpdate(shared_from_this());
}

void Camera::SortGameObject()
{
    m_vForwardObjects.clear();
    m_vDeferredObjects.clear();
    m_vParticleObjects.clear();

    shared_ptr<Scene> pCurScene = GET_SINGLE(Scenes)->GetActiveScene();

    for (int32 i = 0; i < LAYER_TYPE_COUNT; ++i)
    {
        if (m_iCullingMask & (1 << i))
            continue;

        const std::vector<shared_ptr<GameObject>>& vGameObjects = pCurScene->GetGameObjects(static_cast<LAYER_TYPE>(i));
        for (const shared_ptr<GameObject>& pGameObject : vGameObjects)
        {
            if (pGameObject->IsDisable())
                continue;

            if (nullptr == pGameObject->GetMeshRenderer() &&
                nullptr == pGameObject->GetParticleSystem() &&
                LAYER_TYPE::PLAYER != pGameObject->GetLayerType())
                continue;

            if (pGameObject->IsFrustum() && pGameObject->GetTransform())
            {
                if (false == m_Frustum.ContainsSphere(
                    pGameObject->GetTransform()->GetWorldPosition(),
                    pGameObject->GetTransform()->GetBoundingSphereRadius()))
                    continue;
            }
            
            if (pGameObject->GetMeshRenderer())
            {
                SHADER_TYPE eShaderType = pGameObject->GetMeshRenderer()->GetMaterial()->GetShader()->GetShaderType();
                switch (eShaderType)
                {
                case SHADER_TYPE::FORWARD:
                    m_vForwardObjects.push_back(pGameObject);
                    break;
                case SHADER_TYPE::DEFERRED:
                    m_vDeferredObjects.push_back(pGameObject);
                    break;
                }
            }
            else
            {
                if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
                    m_vDeferredObjects.push_back(pGameObject);

                if (pGameObject->GetParticleSystem())
                    m_vForwardObjects.push_back(pGameObject);
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

void Camera::SetLimitRect(const Vec4& vLimitRect)
{
    m_vLimitRect = vLimitRect;
}

void Camera::SetTargetPos(const Vec3& vPos, float fTime)
{
    assert(m_vTargetPos == Vec3::Zero);
    m_vTargetPos = vPos;
    m_tTrackingTimer.SetEndTime(fTime);
    m_tTrackingTimer.Start();

    Vec3 vMyPos = GetTransform()->GetLocalPosition();
    m_vTargetPos.z = vMyPos.z;

    m_vInitDir =  m_vTargetPos - vMyPos;
    float fLength = m_vInitDir.Length();
    m_fTrackingSpeed = fLength / fTime;

    m_vInitDir.Normalize();
}

void Camera::Render_Forward()
{
    for (const auto& pGameObject : m_vForwardObjects)
    {
        if (pGameObject->GetMeshRenderer())
            pGameObject->GetMeshRenderer()->Render(shared_from_this());  
        
        if (pGameObject->GetParticleSystem())
            pGameObject->GetParticleSystem()->Render(shared_from_this());

 /*       if (pGameObject->GetDebugRenderer())
            pGameObject->GetDebugRenderer()->Render(shared_from_this());*/
    }
}

void Camera::Render_Deferred()
{
    for (const auto& pGameObject : m_vDeferredObjects)
    {
        if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
        {
            weak_ptr<Skul> pActiveSkul = static_pointer_cast<Player>(pGameObject)->GetActiveSkul();
            if (pActiveSkul.lock() && pActiveSkul.lock()->IsEnable())
                pActiveSkul.lock()->GetMeshRenderer()->Render(shared_from_this());
        }
        else
            pGameObject->GetMeshRenderer()->Render(shared_from_this());

        if (m_bDebugMode)
        {
            if (pGameObject->GetDebugRenderer())
                pGameObject->GetDebugRenderer()->Render(shared_from_this());
        }
    }
}
