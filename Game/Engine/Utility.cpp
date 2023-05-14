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
	std::array<std::vector<ComPtr<ID3D11ShaderResourceView>>, SRV_KIND_COUNT> vSRV;

	// Tiles
	const wstring szTileDir = L"..\\Resources\\Texture\\Tiles\\";
	uint32 iCount = 0;
	for (const auto& file : fs::directory_iterator(szTileDir))
	{
		wstring fileName = file.path().filename().wstring();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szTileDir + fileName, szTileDir + fileName);

		m_mSRVMap[iCount] = szTileDir + fileName;
		vSRV[static_cast<uint8>(SRV_KIND::TILE)].push_back(pTexture->GetSRV());

		iCount++;
	}

	// Dungeon Gate
	const wstring szDungeonObjectDir = L"..\\Resources\\Texture\\DungeonObject\\";
	
	for (const auto& file : fs::directory_iterator(szDungeonObjectDir))
	{
		wstring fileName = file.path().filename().wstring();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szDungeonObjectDir + fileName, szDungeonObjectDir + fileName);

		m_mSRVMap[iCount] = szDungeonObjectDir + fileName;

		const size_t iUnderbarIdx = fileName.find(L'_');
		wstring szSplit = fileName.substr(0, iUnderbarIdx);
		if (L"GateImage" == szSplit)
		{
			vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_GATE)].push_back(pTexture->GetSRV());
		}

		else if (L"WallImage" == szSplit)
		{
			vSRV[static_cast<uint8>(SRV_KIND::DUNGEON_WALL)].push_back(pTexture->GetSRV());
		}

		else if (L"DecoImage" == szSplit)
		{
			vSRV[static_cast<uint8>(SRV_KIND::DECO_OBJECT)].push_back(pTexture->GetSRV());
		}

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
	auto iter = m_mSRVMap.find(g_pTool->GetMapEditor()->GetClickedTileIndex());
	if (iter == m_mSRVMap.end())
	{
		return L"FAILURE";
	}

	return iter->second;
}
