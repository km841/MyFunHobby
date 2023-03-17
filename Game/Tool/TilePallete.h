#pragma once
#include "Common.h"
#include "GuiBase.h"

class TilePallete
	: public GuiBase
{
public:
	TilePallete();
	~TilePallete();

public:
	void Init(const std::vector<ComPtr<ID3D11ShaderResourceView>>& vSRV);
	void Update();


public:
	int32 GetClickedTileIndex()    { return m_iClickedTileIndex; }
	void  ClearClickedTile()       { m_iClickedTileIndex = -1; }
	bool  IsMouseNotOver()         { return !m_bMouseOver; }
	 
	uint8 GetClickedColliderType() { return m_iClickedColliderType; }
	uint8 GetDrawingType()         { return m_iDrawingType; }
	uint8 GetOutputType()          { return m_iOutputType; }

private:
	void ColliderTypeUI_Update();
	void DrawingTypeUI_Update();
	void TileButtonUI_Update();
	void OutputTypeUI_Update();
	void UpdateOptionSelection();
	void UpdateTileSelection();
	void UpdateUIHoverState();

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
	int32 m_iOutputType;

	bool m_bMouseOver;
};

