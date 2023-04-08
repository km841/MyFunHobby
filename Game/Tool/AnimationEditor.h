#pragma once
#include "Common.h"
#include "GuiBase.h"

enum
{
	NAME_MAX_SIZE = 1024,
};

class AnimationEditor
	: public GuiBase
{
public:
	AnimationEditor();
	~AnimationEditor();

public:
	void Init();
	void Update();

	FORCEINLINE bool						  HasAtlasTexture() const		 { return m_bHasAtlasTexture; }
	FORCEINLINE const wstring&				  GetSpriteTexturePath() const	 { return m_szSpriteTexturePath; }
	void									  EnableSpriteTexture()			 { m_bHasAtlasTexture = true; }
	void									  ClearSpriteTexturePath()		 { m_szSpriteTexturePath.clear(); }
	wstring									  GetAnimationName()			 { return s2ws(string(m_szName)); }

public:							  
	FORCEINLINE const ImVec2&				  GetSpriteLTPoint() const		 { return m_vLTPos; }
	FORCEINLINE const ImVec2&				  GetSpriteSize() const			 { return m_vSize; }
	FORCEINLINE float						  GetDuration()	const			 { return m_fDuration; }
	FORCEINLINE const ImVec2&				  GetOffset() const				 { return m_vOffset; }
	void									  FlipReadableFlag()			 { m_bReadable = (m_bReadable + 1) % 2; }
	FORCEINLINE bool						  IsReadable() const			 { return m_bReadable; }  
	void									  ClearFrameDataList()			 { m_vFrameDataList.clear(); }	  
	FORCEINLINE bool						  GetAnimPlayingFlag() const	 { return m_bPlaying; }
	void									  FlipAnimPlayingFlag()			 { m_bPlaying = (m_bPlaying + 1) % 2; }
	FORCEINLINE const std::vector<FrameData>& GetFrameDataList() const		 { return m_vFrameDataList; }
	FORCEINLINE bool						  IsSpriteUpdate() const		 { return m_bSpriteUpdate; }
	void									  SpriteUpdateEnable()			 { m_bSpriteUpdate = true; }
	void									  SpriteUpdateDisable()			 { m_bSpriteUpdate = false; }

	void									  InsertFrameData(const FrameData& frameData);

private:
	void									  NewButtonUI_Update();
	void									  OpenButtonUI_Update();
	void									  SaveButtonUI_Update();
	void									  SetButtonUI_Update();
	void									  InputUI_Update();
	void									  EditUI_Update();
	void									  FrameListUI_Update();
	void									  AnimUI_Update();

private:
	wstring m_szSpriteTexturePath;

	char   m_szName[NAME_MAX_SIZE];
	ImVec2 m_vLTPos;
	ImVec2 m_vSize;
	ImVec2 m_vOffset;
	float  m_fDuration;

	bool   m_bSpriteUpdate;
	bool   m_bHasAtlasTexture;
	bool   m_bReadable;
	bool   m_bLoop;
	bool   m_bPlaying;
	bool   m_bAllChange;

	FrameData m_CurrFrameData;
	std::vector<FrameData> m_vFrameDataList;
	int32 m_iFrameSelector;
};

