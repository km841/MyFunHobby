#include "pch.h"
#include "RenderTargetGroup.h"
#include "Engine.h"
#include "Texture.h"

void RenderTargetGroup::Create(RENDER_TARGET_GROUP_TYPE eType, std::vector<RenderTarget>& vRTVec, shared_ptr<Texture> pDSTexture)
{
	m_eType = eType;
	m_vRTVec = vRTVec;
	m_pDSTexture = pDSTexture;
	m_iRTCount = static_cast<uint32>(vRTVec.size());
}

void RenderTargetGroup::OMSetRenderTarget()
{
	std::vector<ID3D11RenderTargetView*> vRenderTargets(m_iRTCount);

	for (uint32 i = 0; i < m_iRTCount; ++i)
	{
		vRenderTargets[i] = m_vRTVec[i].pTarget->GetRTV().Get();
	}

	CONTEXT->OMSetRenderTargets(m_iRTCount, vRenderTargets.data(), m_pDSTexture->GetDSV().Get());
}

void RenderTargetGroup::OMSetRenderTarget(int32 iIndex)
{
	CONTEXT->OMSetRenderTargets(iIndex, m_vRTVec[0].pTarget->GetRTV().GetAddressOf(), m_pDSTexture->GetDSV().Get());
}

void RenderTargetGroup::ClearRenderTargetView()
{
	for (uint32 i = 0; i < m_iRTCount; ++i)
	{
		CONTEXT->ClearRenderTargetView(m_vRTVec[i].pTarget->GetRTV().Get(), m_vRTVec[i].fClearColors);
	}
	
	CONTEXT->ClearDepthStencilView(m_pDSTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}
