#pragma once
#include "Common.h"
class AnimationEditor
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
	const wstring& GetAtlasTextureKey() { return m_szAtlasTextureKey; }
	const wstring& GetAtlasTexturePath() { return m_szAtlasTexturePath; }
	void		   EnableAtlasTexture() { m_bHasAtlasTexture = true; }
	void		   ClearAtlasTexturePath() { m_szAtlasTexturePath.clear(); }

private:
	ImVec2 m_vWindowSize;
	wstring m_szAtlasTextureKey;
	wstring m_szAtlasTexturePath;

	bool m_bHasAtlasTexture;
};

