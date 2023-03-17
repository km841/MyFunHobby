#pragma once
#include "Common.h"
#include "GuiBase.h"

struct FrameData
{
	ImVec2 vLTPos;
	ImVec2 vSize;
	float  fDuration;
	float  fOffset;
	int32  iFrameCount;
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

	bool           HasAtlasTexture() { return m_bHasAtlasTexture; }
	const wstring& GetSpriteTextureKey() { return m_szSpriteTextureKey; }
	const wstring& GetSpriteTexturePath() { return m_szSpriteTexturePath; }
	void		   EnableSpriteTexture() { m_bHasAtlasTexture = true; }
	void		   ClearSpriteTexturePath() { m_szSpriteTexturePath.clear(); }

public:
	const ImVec2&  GetSpriteLTPoint() { return m_vLTPos; }
	const ImVec2&  GetSpriteSize()    { return m_vSize; }
	float		   GetDuration()      { return m_fDuration; }
	float		   GetOffset()		  { return m_fOffset; }
	void		   FlipReadableFlag() { m_bReadable = (m_bReadable + 1) % 2; }
	bool		   IsReadable()		  { return m_bReadable; }

	void		   InsertFrameData(const FrameData& frameData);
	void		   ClearFrameDataList() { m_vFrameDataList.clear(); }
private:
	

private:
	ImVec2 m_vWindowSize;
	wstring m_szSpriteTextureKey;
	wstring m_szSpriteTexturePath;

	ImVec2 m_vLTPos;
	ImVec2 m_vSize;
	float m_fDuration;
	float m_fOffset;

	bool m_bHasAtlasTexture;
	bool m_bReadable;

	FrameData m_CurrFrameData;
	std::vector<FrameData> m_vFrameDataList;
	int32 m_iFrameSelector;
};

