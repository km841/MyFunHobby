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

void Material::PushGraphicData()
{
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&m_materialParams, sizeof(m_materialParams));

	SHADER_TYPE eShaderType = m_pShader->GetShaderType();

	for (uint32 i = 0; i < m_pTextures.size(); ++i)
	{
		if (nullptr == m_pTextures[i])
		{
			CONTEXT->PSSetShaderResources(static_cast<uint8>(SRV_REGISTER::t0) + i, 1,
				reinterpret_cast<ID3D11ShaderResourceView**>(&m_ppNullptr));
		}

		else
		{
			CONTEXT->PSSetShaderResources(static_cast<uint8>(SRV_REGISTER::t0) + i, 1,
				m_pTextures[i]->GetSRV().GetAddressOf());
		}

	}
	
	m_pShader->Update();
}

void Material::PushComputeData()
{
	CONST_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&m_materialParams, sizeof(m_materialParams));

	for (uint32 i = 0; i < m_pTextures.size(); ++i)
	{
		if (nullptr == m_pTextures[i])
		{
			CONTEXT->CSSetUnorderedAccessViews(static_cast<uint8>(UAV_REGISTER::u0) + i, 1,
				reinterpret_cast<ID3D11UnorderedAccessView**>(&m_ppNullptr), 0);
		}

		else
		{
			CONTEXT->CSSetUnorderedAccessViews(static_cast<uint8>(UAV_REGISTER::u0) + i, 1,
				m_pTextures[i]->GetUAV().GetAddressOf(), 0);
		}
	}

	m_pShader->Update();
}

void Material::Dispatch(uint32 iCountX, uint32 iCountY, uint32 iCountZ)
{
	PushComputeData();
	CONTEXT->Dispatch(iCountX, iCountY, iCountZ);
	ClearComputeData();
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

void Material::ClearComputeData()
{
	for (uint32 i = 0; i < m_pTextures.size(); ++i)
	{
		CONTEXT->CSSetUnorderedAccessViews(static_cast<uint8>(UAV_REGISTER::u0) + i, 1,
			reinterpret_cast<ID3D11UnorderedAccessView**>(&m_ppNullptr), 0);
	}
}
