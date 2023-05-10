#include "pch.h"
#include "Light.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"
#include "Player.h"
#include "Skul.h"

Light::Light()
	: Component(COMPONENT_TYPE::LIGHT)
	, m_iLightIndex(-1)
{
}

Light::~Light()
{
}

void Light::FinalUpdate()
{
	m_LightInfo.vPosition = GetGameObject()->GetTransform()->GetWorldPosition();
	m_LightInfo.vPosition.x += m_vLightOffset.x;
	m_LightInfo.vPosition.y += m_vLightOffset.y;
}

void Light::Render(shared_ptr<Camera> pCamera)
{
	assert(m_iLightIndex >= 0);

	GetTransform()->PushData(pCamera);

	m_pMaterial->SetInt(0, m_iLightIndex);
	m_pMaterial->PushGraphicData();

	switch (static_cast<LIGHT_TYPE>(m_LightInfo.eLightType))
	{
	case LIGHT_TYPE::SPOT_LIGHT:
	case LIGHT_TYPE::POINT_LIGHT:
		float fScale = m_LightInfo.fRange;
		GetTransform()->SetLocalScale(Vec3(fScale, fScale, fScale));
		break;
	}

	m_pMesh->Render();
}

void Light::SetLightType(LIGHT_TYPE eLightType)
{
	m_LightInfo.eLightType = static_cast<int32>(eLightType);

	switch (eLightType)
	{
	case LIGHT_TYPE::DIRECTIONAL_LIGHT:
		m_pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		m_pMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight")->Clone();
		break;
	case LIGHT_TYPE::POINT_LIGHT:
		m_pMesh = GET_SINGLE(Resources)->LoadCircleMesh();
		m_pMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight")->Clone();
		break;
	case LIGHT_TYPE::SPOT_LIGHT:
		m_pMesh = GET_SINGLE(Resources)->LoadCircleMesh();
		m_pMaterial = GET_SINGLE(Resources)->Get<Material>(L"PointLight")->Clone();
		break;
	}
}
