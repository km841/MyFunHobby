#include "pch.h"
#include "GridDrawScript.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Camera.h"
#include "Engine.h"
#include "Transform.h"

GridDrawScript::GridDrawScript(shared_ptr<Camera> pCamera)
	: m_pCamera(pCamera)
	, m_fThickness(3.f)
	, m_vGridOffset{ 102.5f, 102.5f }
{
}

GridDrawScript::~GridDrawScript()
{
}

void GridDrawScript::LateUpdate()
{
	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	Vec3 vCamPos = m_pCamera->GetTransform()->GetLocalPosition();
	
	GetMeshRenderer()->GetMaterial()->SetFloat(0, m_fThickness);
	GetMeshRenderer()->GetMaterial()->SetVec2(0, Vec2(fWidth, fHeight));
	GetMeshRenderer()->GetMaterial()->SetVec2(1, m_vGridOffset);
	GetMeshRenderer()->GetMaterial()->SetVec3(0, vCamPos);
}
