#pragma once
#include "FW1FontWrapper.h"

enum class FONT_WEIGHT
{
	LIGHT, 
	NORMAL,
	BOLD,
	ULTRA_BOLD,
	END,
};

enum
{
	FONT_WEIGHT_COUNT = FONT_WEIGHT::END,
};

struct FontInfo
{
	wstring szText;
	float fFontSize;
	Vec3 vFontPos;
	FONT_WEIGHT eFontWeight;
	uint32 iFontColor;
};

class Font
{
public:
	DECLARE_SINGLE(Font);

public:
	// Font를 오브젝트 단위로 관리할 필요가 없다!
	void Init();
	void DrawString(const wstring& szText, float fFontSize, const Vec3& vPos, FONT_WEIGHT eWeight = FONT_WEIGHT::NORMAL, uint32 iColor = 0xffffffff);
	void Render();

private:
	void CreateFontWrapperGroup();

private:
	std::array<ComPtr<IFW1FontWrapper>, FONT_WEIGHT_COUNT> m_arrFontWrapperGroup;
	ComPtr<IDWriteFactory> m_pWriteFactory;
	ComPtr<IFW1Factory> m_pFontFactory;

	int32 m_iWindowHeight;

	std::queue<FontInfo> m_qFontQueue;
};

