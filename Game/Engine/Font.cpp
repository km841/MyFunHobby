#include "pch.h"
#include "Font.h"

Font::Font()
	: m_iWindowHeight(0)
{
}

Font::~Font()
{
}

void Font::Init(const WindowInfo& windowInfo, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	m_pDevice = pDevice;
	m_pContext = pContext;
	m_iWindowHeight = windowInfo.iHeight;

	FW1CreateFactory(FW1_VERSION, m_pFontFactory.GetAddressOf());
	assert(m_pFontFactory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(m_pWriteFactory.GetAddressOf()));
	CreateFontWrapperGroup();
}

void Font::DrawString(const wstring& szText, float fFontSize, const Vec3& vPos, FONT_WEIGHT eWeight, uint32 iColor)
{
	Vec3 vNewPos = vPos;

	vNewPos.y = m_iWindowHeight - vPos.y;
	m_qFontQueue.push(FontInfo{ szText, fFontSize, vNewPos, eWeight, iColor });
}

void Font::Render()
{
	while (!m_qFontQueue.empty())
	{
		FontInfo fontInfo = m_qFontQueue.front();
		m_qFontQueue.pop();

		m_arrFontWrapperGroup[static_cast<uint8>(fontInfo.eFontWeight)]->DrawString(
			m_pContext.Get(), 
			fontInfo.szText.c_str(), 
			fontInfo.fFontSize, 
			fontInfo.vFontPos.x, 
			fontInfo.vFontPos.y, 
			fontInfo.iFontColor, 
			FW1_RESTORESTATE | FW1_CENTER);
	}
}

void Font::CreateFontWrapperGroup()
{
	FW1_FONTWRAPPERCREATEPARAMS createParams = {};

	createParams.GlyphSheetWidth = 512;
	createParams.GlyphSheetHeight = 512;
	createParams.MaxGlyphCountPerSheet = 2048;
	createParams.SheetMipLevels = 1;
	createParams.AnisotropicFiltering = FALSE;
	createParams.MaxGlyphWidth = 384;
	createParams.MaxGlyphHeight = 384;
	createParams.DisableGeometryShader = FALSE;
	createParams.VertexBufferSize = 0;
	createParams.DefaultFontParams.pszFontFamily = L"Arial";;
	createParams.DefaultFontParams.FontStyle = DWRITE_FONT_STYLE_NORMAL;
	createParams.DefaultFontParams.FontStretch = DWRITE_FONT_STRETCH_NORMAL;
	createParams.DefaultFontParams.pszLocale = L"";
	
	createParams.DefaultFontParams.FontWeight = DWRITE_FONT_WEIGHT_LIGHT;
	HRESULT hr = m_pFontFactory->CreateFontWrapper(m_pDevice.Get(), 
		m_pWriteFactory.Get(), &createParams, m_arrFontWrapperGroup[static_cast<uint8>(FONT_WEIGHT::LIGHT)].GetAddressOf());
	assert(SUCCEEDED(hr));

	createParams.DefaultFontParams.FontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	hr = m_pFontFactory->CreateFontWrapper(m_pDevice.Get(),
		m_pWriteFactory.Get(), &createParams, m_arrFontWrapperGroup[static_cast<uint8>(FONT_WEIGHT::NORMAL)].GetAddressOf());
	assert(SUCCEEDED(hr));

	createParams.DefaultFontParams.FontWeight = DWRITE_FONT_WEIGHT_BOLD;
	hr = m_pFontFactory->CreateFontWrapper(m_pDevice.Get(),
		m_pWriteFactory.Get(), &createParams, m_arrFontWrapperGroup[static_cast<uint8>(FONT_WEIGHT::BOLD)].GetAddressOf());
	assert(SUCCEEDED(hr));

	createParams.DefaultFontParams.FontWeight = static_cast<DWRITE_FONT_WEIGHT>(999);
	hr = m_pFontFactory->CreateFontWrapper(m_pDevice.Get(),
		m_pWriteFactory.Get(), &createParams, m_arrFontWrapperGroup[static_cast<uint8>(FONT_WEIGHT::ULTRA_BOLD)].GetAddressOf());
	assert(SUCCEEDED(hr));
}

