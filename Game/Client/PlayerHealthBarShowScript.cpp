#include "pch.h"
#include "PlayerHealthBarShowScript.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"
#include "Clock.h"
#include "HealthBarHUD.h"
#include "Scenes.h"
#include "Transform.h"
#include "Engine.h"
#include "ComponentObject.h"
#include "Scene.h"

PlayerHealthBarShowScript::PlayerHealthBarShowScript(shared_ptr<HealthBarHUD> pHealthBar)
	: m_pHealthBar(pHealthBar)
	, m_fPrevHP(0.f)
	, m_fDiff(0.f)
{
}

PlayerHealthBarShowScript::~PlayerHealthBarShowScript()
{
}

void PlayerHealthBarShowScript::LateUpdate()
{
	// 기존 hp에서 현재 hp를 뺀다
	float fCurHP = static_cast<float>(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iCurHP);
	if (m_fPrevHP > fCurHP)
	{
		m_fDiff = m_fPrevHP - fCurHP;
	}

	float fRatio = m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->GetHPRatio();
	if (m_fDiff > 0.f)
	{
		m_fDiff -= 30.f * OBJECT_DELTA_TIME;
		fCurHP += m_fDiff;

		fRatio = fCurHP / m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iMaxHP;
	}

	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);

	wstring szMaxHP = std::to_wstring(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iMaxHP);
	wstring szCurHP = std::to_wstring(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iCurHP);

	if (!GET_SINGLE(Clock)->IsPause())
		FONT->DrawString(szCurHP + L" / " + szMaxHP, 23.f, Vec3(280.f, 87.f, 1.f), FONT_WEIGHT::BOLD, 0xffffffff);

	m_fPrevHP = static_cast<float>(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iCurHP);
}
