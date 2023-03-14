#pragma once
#include "Common.h"

class TilePallete
{
public:
	TilePallete();
	~TilePallete();

public:
	void Init(const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV);
	void Update();

public:
	int32 GetClickedTileIndex() { return m_iClickedTileIndex; }
	void  ClearClickedTile() { m_iClickedTileIndex = -1; }

private:
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_vSRV;

	float m_fTileSize;
	float m_fSpacing;
	float m_fTileWindowWidth;

	ImVec2 m_vTileWindowSize;
	ImVec2 m_vWindowPos;

	int32 m_iClickedTileIndex;
};

