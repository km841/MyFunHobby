#include "pch.h"
#include "PlayerHealthBarShowScript.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"

PlayerHealthBarShowScript::PlayerHealthBarShowScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

PlayerHealthBarShowScript::~PlayerHealthBarShowScript()
{
}

void PlayerHealthBarShowScript::LateUpdate()
{
	float fRatio = m_pPlayer.lock()->GetStatus().GetHPRatio();

	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	GetMeshRenderer()->GetMaterial()->SetVec2(0, Vec2(80.f, 10.f));
}
