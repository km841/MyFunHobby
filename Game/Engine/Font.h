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
	Font();
	~Font();

public:
	// Font�� ������Ʈ ������ ������ �ʿ䰡 ����!
	void Init(const WindowInfo& windowInfo, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	void DrawString(const wstring& szText, float fFontSize, const Vec3& vPos, FONT_WEIGHT eWeight = FONT_WEIGHT::NORMAL, uint32 iColor = 0xffffffff);
	void Render();

private:
	void CreateFontWrapperGroup();

private:
	std::array<ComPtr<IFW1FontWrapper>, FONT_WEIGHT_COUNT> m_arrFontWrapperGroup;
	std::queue<FontInfo> m_qFontQueue;
	int32 m_iWindowHeight;

	ComPtr<IDWriteFactory> m_pWriteFactory;
	ComPtr<IFW1Factory> m_pFontFactory;
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<ID3D11DeviceContext> m_pContext;
};
