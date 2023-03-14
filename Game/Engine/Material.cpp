#include "pch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Engine.h"
#include "ConstantBuffer.h"

Material::Material()
	: Object(OBJECT_TYPE::MATERIAL)
	, m_ppNullptr(nullptr)
{
}

Material::~Material()
{
}

void Material::PushData()
{
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&m_materialParams, sizeof(m_materialParams));

	for (uint32 i = 0; i < m_pTextures.size(); ++i)
	{
		if (nullptr == m_pTextures[i])
			CONTEXT->PSSetShaderResources(static_cast<uint8>(SRV_REGISTER::t0) + i, 1, 
				reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));

		else
			CONTEXT->PSSetShaderResources(static_cast<uint8>(SRV_REGISTER::t0) + i, 1, 
				m_pTextures[i]->GetSRV().GetAddressOf());
	}

	m_pShader->Update();
}

void Material::SetTexture(uint8 iIndex, shared_ptr<Texture> pTexture)
{
	m_pTextures[iIndex] = pTexture;
	m_materialParams.SetTexOn(iIndex, 1);
}

shared_ptr<Material> Material::Clone()
{
	shared_ptr<Material> pMaterial = make_shared<Material>();

	pMaterial->SetShader(m_pShader);
	pMaterial->m_materialParams = m_materialParams;
	pMaterial->m_pTextures = m_pTextures;

	return pMaterial;
}