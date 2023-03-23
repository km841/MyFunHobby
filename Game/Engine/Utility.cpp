#include "pch.h"
#include "Utility.h"
#include "Texture.h"
#include "Resources.h"
#include "Tool.h"
#include "Engine.h"

Utility::Utility()
{
	m_szTexPath = L"..\\Resources\\Texture\\";
}

Utility::~Utility()
{
}

void Utility::Init(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	const wstring szTileDir = L"..\\Resources\\Texture\\Tiles\\";
	std::vector<ComPtr<ID3D11ShaderResourceView>> vSRV;

	uint32 iCount = 0;
	for (const auto& file : fs::directory_iterator(szTileDir))
	{
		wstring fileName = file.path().filename().wstring();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTileDir + fileName, szTileDir + fileName);

		m_mTileRrcMap[iCount] = szTileDir + fileName;
		vSRV.push_back(pTexture->GetSRV());

		iCount++;
	}

	assert(!vSRV.empty());
	g_pTool->Init(g_pEngine->GetHwnd(), pDevice, pContext, vSRV);
}

void Utility::ToolUpdate()
{
	g_pTool->Update();
}

void Utility::ToolRender()
{
	g_pTool->Render();

	// 해당 리소스를 통해 마우스 위치에 그려준다.
	// 그 텍스쳐를 가진 gameobject가 있어야 하며,
	// 다른 버튼이 눌리면 이미지를 바꿀 수 있도록 해야 한다



}

wstring Utility::GetSelectedTileKey()
{
	auto iter = m_mTileRrcMap.find(g_pTool->GetPallete()->GetClickedTileIndex());
	if (iter == m_mTileRrcMap.end())
	{
		return L"FAILURE";
	}

	return iter->second;
}
