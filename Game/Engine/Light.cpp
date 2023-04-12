#include "pch.h"
#include "Light.h"
#include "Transform.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

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
	m_LightInfo.vPosition = GetTransform()->GetWorldPosition();
}

void Light::Render(shared_ptr<Camera> pCamera)
{
	assert(m_iLightIndex >= 0);

	GetTransform()->PushData(pCamera);

	m_pMaterial->SetInt(0, m_iLightIndex);
	m_pMaterial->PushGraphicData();

	switch (static_cast<LIGHT_TYPE>(m_LightInfo.eLightType))
	{
	case LIGHT_TYPE::DIRECTIONAL_LIGHT:
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
		m_pMaterial = GET_SINGLE(Resources)->Get<Material>(L"DirLight");
		break;
	case LIGHT_TYPE::POINT_LIGHT:
		break;
	case LIGHT_TYPE::SPOT_LIGHT:
		break;
	}
}
