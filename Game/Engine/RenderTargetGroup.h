#pragma once
#include "Texture.h"

enum class RENDER_TARGET_GROUP_TYPE : uint8
{
	SWAP_CHAIN,
	G_BUFFER,
	LIGHTING,
	END,
};

enum
{
	RENDER_TARGET_GROUP_TYPE_COUNT = RENDER_TARGET_GROUP_TYPE::END,
	G_BUGGER_GROUP_COUNT = 3,
	SWAP_CHAIN_BUFFER_COUNT = 1,
};

struct RenderTarget
{
	shared_ptr<Texture> pTarget;
	float fClearColors[4];
};

class RenderTargetGroup
{
public:
	void Create(RENDER_TARGET_GROUP_TYPE eType, std::vector<RenderTarget>& vRTVec, shared_ptr<Texture> pDSTexture);

	void OMSetRenderTarget();
	void OMSetRenderTarget(int32 iIndex);
	void ClearRenderTargetView();

private:
	RENDER_TARGET_GROUP_TYPE	 m_eType;
	std::vector<RenderTarget>	 m_vRTVec;
	uint32					     m_iRTCount;
	shared_ptr<Texture>		     m_pDSTexture;
};

