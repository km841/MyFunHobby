#include "pch.h"
#include "Font.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "ComponentObject.h"
#include "Clock.h"

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

void Font::DrawStringAtWorldPos(const wstring& szText, float fFontSize, const Vec3& vWorldPos, FONT_WEIGHT eWeight, uint32 iColor)
{
	Vec3 vScreenPos = GET_SINGLE(Scenes)->WorldToScreenPosition(
		vWorldPos, GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera());

	m_qFontQueue.push(FontInfo{ szText, fFontSize, vScreenPos, eWeight, iColor });
}

void Font::DrawDamage(DAMAGE_TYPE eDamageType, float fDamage, const Vec3& vPos)
{
	// 변화하는 위치값만 가지고 관리하면 된다.
	// 글자 색상, 크기는 정해져 있기 때문

	// 데미지 구조체를 두고, 시간 간격에 따라 올라갔다가 내려오는 모션

	Vec3 vNewVec = vPos;
	vNewVec.y += 30.f;
	m_vDamages.push_back(DamageInfo{ eDamageType, 0.5f, fDamage, vNewVec });
}

void Font::UpdateDamage()
{
	for (auto iter = m_vDamages.begin(); iter != m_vDamages.end(); )
	{
		DamageInfo& damageInfo = *iter;
		if (!damageInfo.tDuration.IsRunning())
			damageInfo.tDuration.Start();

		if (damageInfo.tDuration.IsFinished())
		{
			iter = m_vDamages.erase(iter);
		}
		else
		{
			float fRatio = damageInfo.tDuration.GetProgress();
			damageInfo.vDamagePos.y += sinf(fRatio * XM_PI * 1.5f);

			float fFontSize = 30.f;
			if (damageInfo.fDamage > 50.f)
				fFontSize = 50.f;
			else if (damageInfo.fDamage > 30.f)
				fFontSize = 40.f;
			else if (damageInfo.fDamage > 10.f)
				fFontSize = 35.f;

			Vec3 vOutlinePos = damageInfo.vDamagePos;
			vOutlinePos.y += 1.f;

			DrawStringAtWorldPos(std::to_wstring(static_cast<int32>(damageInfo.fDamage)), fFontSize, vOutlinePos, FONT_WEIGHT::BOLD, 0xff000000);
			switch (damageInfo.eDamageType)
			{
			case DAMAGE_TYPE::FROM_MONSTER:
				DrawStringAtWorldPos(std::to_wstring(static_cast<int32>(damageInfo.fDamage)), fFontSize, damageInfo.vDamagePos, FONT_WEIGHT::NORMAL, Color::FromRGB(196, 67, 45));
				break;
			case DAMAGE_TYPE::FROM_PLAYER_MELEE:
				DrawStringAtWorldPos(std::to_wstring(static_cast<int32>(damageInfo.fDamage)), fFontSize, damageInfo.vDamagePos, FONT_WEIGHT::NORMAL, 0xffffffff);
				break;
			case DAMAGE_TYPE::FROM_PLAYER_MAGIC:
				DrawStringAtWorldPos(std::to_wstring(static_cast<int32>(damageInfo.fDamage)), fFontSize, damageInfo.vDamagePos, FONT_WEIGHT::NORMAL, Color::FromRGB(106, 243, 233));
				break;
			case DAMAGE_TYPE::FROM_PLAYER_CRITICAL:
				DrawStringAtWorldPos(std::to_wstring(static_cast<int32>(damageInfo.fDamage)), fFontSize, damageInfo.vDamagePos, FONT_WEIGHT::NORMAL, Color::FromRGB(240, 191, 63));
				break;
			}

			damageInfo.tDuration.Update(DELTA_TIME);
			iter++;
		}
	}
}

void Font::Render()
{
	UpdateDamage();
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

