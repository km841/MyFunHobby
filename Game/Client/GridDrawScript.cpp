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
	, m_vGridOffset{ 100.f, 100.f }
{
}

GridDrawScript::~GridDrawScript()
{
}

void GridDrawScript::LateUpdate()
{
	int32 iWidth = g_pEngine->GetWidth();
	int32 iHeight = g_pEngine->GetHeight();

	Vec3 vCamPos = m_pCamera->GetTransform()->GetLocalPosition();
	
	GetMeshRenderer()->GetMaterial()->SetFloat(0, m_fThickness);
	GetMeshRenderer()->GetMaterial()->SetVec2(0, Vec2(iWidth, iHeight));
	GetMeshRenderer()->GetMaterial()->SetVec2(1, m_vGridOffset);
	GetMeshRenderer()->GetMaterial()->SetVec3(0, vCamPos);
}
