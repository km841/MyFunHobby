#include "pch.h"
#include "PlayerHealthBarShowScript.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Engine.h"
#include "Transform.h"
#include "Clock.h"
#include "HealthBarHUD.h"

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
}
