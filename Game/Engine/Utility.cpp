#include "pch.h"
#include "Utility.h"
#include "Texture.h"
#include "Resources.h"
#include "Tool.h"
#include "Engine.h"

Utility::Utility()
{
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
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(fileName, szTileDir + fileName);

		m_mTileRrcMap[iCount] = fileName;
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

	// �ش� ���ҽ��� ���� ���콺 ��ġ�� �׷��ش�.
	// �� �ؽ��ĸ� ���� gameobject�� �־�� �ϸ�,
	// �ٸ� ��ư�� ������ �̹����� �ٲ� �� �ֵ��� �ؾ� �Ѵ�



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
