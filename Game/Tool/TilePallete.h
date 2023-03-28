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
	FORCEINLINE int32 GetClickedTileIndex() const    { return m_iClickedTileIndex; }
	FORCEINLINE void  ClearClickedTile()			 { m_iClickedTileIndex = -1; }
	FORCEINLINE bool  IsMouseNotOver() const		 { return !m_bMouseOver; }
											   
	FORCEINLINE uint8 GetClickedColliderType() const { return m_iClickedColliderType; }
	FORCEINLINE uint8 GetDrawingType() const		 { return m_iDrawingType; }
	FORCEINLINE uint8 GetOutputType() const			 { return m_iOutputType; }

	FORCEINLINE bool IsTileSynced()	const			 { return m_bTileSync; }
	FORCEINLINE void EnableTileSync()				 { m_bTileSync = true; }
	FORCEINLINE void DisableTileSync()				 { m_bTileSync = false; }

	FORCEINLINE bool IsTileSend() const				 { return m_bTileSend; }
	FORCEINLINE void EnableIsTileSend()			 	 { m_bTileSend = true; }
	FORCEINLINE void DisableIsTileSend()		 	 { m_bTileSend = false; }

	void SetTileMapData(const TileMapData& tileMapData);
	FORCEINLINE const TileMapData& GetTileMapData() { return m_TileMapData; }

private:
	void  ColliderTypeUI_Update();
	void  DrawingTypeUI_Update();
	void  TileButtonUI_Update();
	void  OutputTypeUI_Update();
	void  UpdateOptionSelection();
	void  UpdateTileSelection();
	void  UpdateUIHoverState();

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

	TileMapData m_TileMapData;
	bool	    m_bTileSync;
	bool		m_bTileSend;

	bool m_bMouseOver;
};

