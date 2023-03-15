#pragma once
#include "Common.h"

//enum class COLLIDER_TYPE : uint8
//{
//	NONE,
//	WALL,
//	FOOTHOLD,
//};

class TilePallete
{
public:
	TilePallete();
	~TilePallete();

public:
	void Init(const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV);
	void Update();

	void InsertSeparator();
	void ColliderTypeUI_Update();
	void DrawingTypeUI_Update();
	void TileButtonUI_Update();

public:
	int32 GetClickedTileIndex() { return m_iClickedTileIndex; }
	void  ClearClickedTile() { m_iClickedTileIndex = -1; }
	bool IsMouseNotOver() { return !m_bMouseOver; }

	uint8 GetClickedColliderType() { return m_iClickedColliderType; }
	uint8 GetDrawingType() { return m_iDrawingType; }

private:
	std::vector<ComPtr<ID3D11ShaderResourceView>> m_vSRV;

	float m_fTileSize;
	float m_fSpacing;
	float m_fTileWindowWidth;

	ImVec2 m_vTileWindowSize;
	ImVec2 m_vWindowPos;

	int32 m_iClickedTileIndex;
	int32 m_iClickedColliderType;
	int32 m_iDrawingType;

	bool m_bMouseOver;
};

