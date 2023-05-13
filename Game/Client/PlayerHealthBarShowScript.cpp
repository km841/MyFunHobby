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
{
}

PlayerHealthBarShowScript::~PlayerHealthBarShowScript()
{
}

void PlayerHealthBarShowScript::LateUpdate()
{
	float fRatio = m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->GetHPRatio();
	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);

	wstring szMaxHP = std::to_wstring(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iMaxHP);
	wstring szCurHP = std::to_wstring(m_pHealthBar.lock()->GetPlayer().lock()->GetStatus()->iCurHP);

	FONT->DrawString(szCurHP + L" / " + szMaxHP, 23.f, Vec3(280.f, 87.f, 1.f), FONT_WEIGHT::BOLD, 0xffffffff);
}
