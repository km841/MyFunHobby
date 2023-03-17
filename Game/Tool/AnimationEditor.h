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
	// �ؽ��ĸ� �� �� ��������, ī�޶�� �� �ؽ��ĸ� �ѷ����� �ͺ��� �����ؾ� �Ѵ�
	// gui�� ���� ã�� �� ���� ��ư�� ���� �̹����� �����ϸ�, �� �̹����� ȭ�鿡 �� ���� �׷����� �Ѵ�.
	// 
	// Ȯ�� ��Ұ� �����ؾ� �Ѵ�
	// ���� ���콺�� Ŭ���� �κ��� �ؽ����� ��� �κ����� �˾ƾ� �Ѵ�.
	// ����Ű�� �̼� ������ �����ؾ� �Ѵ�
	// ���� �Է��ؼ� �̼� ������ �����ؾ� �Ѵ�
	// �ִϸ��̼� ������ ������ �ǽð� ������ �����ؾ� �ϸ�, ����� �����ؾ� �Ѵ�
	// Ư�� �������� �ڸ��� �ٲٰų� ���� �� �־�� �Ѵ�
	// �ش� �����͸� �����ϰ� �ִϸ����Ϳ��� �ҷ��� �� �־�� �Ѵ�.

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

