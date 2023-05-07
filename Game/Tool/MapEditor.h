#pragma once
#include "Common.h"
#include "GuiBase.h"

class MapEditor
	: public GuiBase
{
public:
	MapEditor();
	~MapEditor();

public:
	void Init(const std::array<std::vector<ComPtr<ID3D11ShaderResourceView>>, SRV_KIND_COUNT>& vSRV);
	void Update();

public:
	FORCEINLINE int32 GetClickedTileIndex() const    { return m_iClickedTileIndex; }
	FORCEINLINE void  ClearClickedTile()			 { m_iClickedTileIndex = -1; }
	FORCEINLINE bool  IsMouseNotOver() const		 { return !m_bMouseOver; }
											   
	FORCEINLINE uint8 GetClickedColliderType() const { return m_iClickedColliderType; }
	FORCEINLINE uint8 GetDrawingType() const		 { return m_iDrawingType; }
	FORCEINLINE uint8 GetOutputType() const			 { return m_iOutputType; }

	FORCEINLINE bool IsDataSynced()	const			 { return m_bDataSync; }
	FORCEINLINE void EnableDataSync()				 { m_bDataSync = true; }
	FORCEINLINE void DisableDataSync()				 { m_bDataSync = false; }

	FORCEINLINE bool IsDataSend() const				 { return m_bDataSend; }
	FORCEINLINE void EnableIsDataSend()			 	 { m_bDataSend = true; }
	FORCEINLINE void DisableIsDataSend()		 	 { m_bDataSend = false; }

	void SetTileMapData(const TileMapData& tileMapData);
	FORCEINLINE const TileMapData& GetTileMapData() { return m_TileMapData; }

	bool IsCreateBGFlag() { return m_bCreateBGFlag; }
	void DisableCreateBGFlag() { m_bCreateBGFlag = false; }

	ImVec3 GetCreateBGPos() { return m_vBGPos; }
	ImVec3 GetCreateBGScale() { return m_vBGScale; }

	const wstring& GetBGImagePath() { return m_szBGImagePath; }
	bool IsChangedBGDataFlag() { return m_bChangedBGDataFlag; }
	void DisableChangedBGDataFlag() { m_bChangedBGDataFlag = false; }
	int32 GetSelectedBGIndex() { return m_iBackgroundDataSelector; }
	const BackgroundData& GetSelectedBGData() { return m_CurrBackgroundData; }
	const std::vector<BackgroundData>& GetBackgroundDataList() { return m_vBackgroundDataList; }

private:
	void  ColliderTypeUI_Update();
	void  DrawingTypeUI_Update();
	void  TileButtonUI_Update();
	void  OutputTypeUI_Update();
	void  UpdateOptionSelection();
	void  UpdateTileSelection();
	void  UpdateUIHoverState();

	void  UpdateBGSelection();
	void  UpdateDOSelection();
	void  UpdateDESelection();

	string ConditionEnumToString(CONDITION_TYPE eConditionType);
	string EventEnumToString(DUNGEON_EVENT_KIND eEventKind);

	void MonsterSpawnEventUIUpdate();
	void PlayerTeleportEventUIUpdate();

	string MonsterKindEnumToString(MONSTER_KIND eMonsterKind);

private:
	std::array<std::vector<ComPtr<ID3D11ShaderResourceView>>, SRV_KIND_COUNT> m_vSRV;

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
	bool	    m_bDataSync;
	bool		m_bDataSend;

	bool m_bMouseOver;

	wstring m_szBGImagePath;
	bool	    m_bCreateBGFlag;
	ImVec3 m_vBGPos;
	ImVec3 m_vBGScale;

	std::vector<BackgroundData> m_vBackgroundDataList;
	int32 m_iBackgroundDataSelector;
	BackgroundData m_CurrBackgroundData;

	bool m_bChangedBGDataFlag;

	bool m_bBackgroundSend;

	EventInfo m_InputEventInfo;
	EventInfo m_CurrEventInfo;
	std::vector<EventInfo> m_vEventList;

	int32 m_iConditionSelector;
	int32 m_iEventSelector;
	int32 m_iEventListSelector;


};

