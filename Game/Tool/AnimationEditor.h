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
	// 텍스쳐를 한 장 가져오고, 카메라로 그 텍스쳐를 둘러보는 것부터 시작해야 한다
	// gui의 파일 찾기 및 열기 버튼을 통해 이미지를 선택하면, 그 이미지가 화면에 꽉 차게 그려져야 한다.
	// 
	// 확대 축소가 가능해야 한다
	// 현재 마우스로 클릭한 부분이 텍스쳐의 어느 부분인지 알아야 한다.
	// 방향키로 미세 조정이 가능해야 한다
	// 값을 입력해서 미세 조정이 가능해야 한다
	// 애니메이션 프레임 단위로 실시간 저장이 가능해야 하며, 재생도 가능해야 한다
	// 특정 프레임의 자리를 바꾸거나 지울 수 있어야 한다
	// 해당 데이터를 저장하고 애니메이터에서 불러올 수 있어야 한다.

	bool						  HasAtlasTexture()        { return m_bHasAtlasTexture; }
	const wstring&				  GetSpriteTextureKey()    { return m_szSpriteTextureKey; }
	const wstring&				  GetSpriteTexturePath()   { return m_szSpriteTexturePath; }
	void						  EnableSpriteTexture()    { m_bHasAtlasTexture = true; }
	void						  ClearSpriteTexturePath() { m_szSpriteTexturePath.clear(); }
								  
	wstring						  GetAnimationName()	   { return s2ws(string(m_szName)); }
								  
public:							  
	const ImVec2&				  GetSpriteLTPoint()	   { return m_vLTPos; }
	const ImVec2&				  GetSpriteSize()		   { return m_vSize; }
	float						  GetDuration()			   { return m_fDuration; }
	const ImVec2&				  GetOffset()			   { return m_vOffset; }
	void						  FlipReadableFlag()	   { m_bReadable = (m_bReadable + 1) % 2; }
	bool						  IsReadable()			   { return m_bReadable; }
								  
	void						  ClearFrameDataList()	   { m_vFrameDataList.clear(); }
								  
	bool						  GetAnimPlayingFlag()	   { return m_bPlaying; }
	void						  FlipAnimPlayingFlag()	   { m_bPlaying = (m_bPlaying + 1) % 2; }
	const std::vector<FrameData>& GetFrameDataList()	   { return m_vFrameDataList; }

	void						  InsertFrameData(const FrameData& frameData);
private:
	

private:
	
	wstring m_szSpriteTextureKey;
	string m_szSpriteTextureKeyStr;
	wstring m_szSpriteTexturePath;

	char m_szName[NAME_MAX_SIZE];
	ImVec2 m_vLTPos;
	ImVec2 m_vSize;
	ImVec2 m_vOffset;
	float m_fDuration;

	bool m_bHasAtlasTexture;
	bool m_bReadable;
	bool m_bLoop;

	bool m_bPlaying;

	FrameData m_CurrFrameData;
	std::vector<FrameData> m_vFrameDataList;
	int32 m_iFrameSelector;
};

