#include "pch.h"
#include "PlayerHealthBarShowScript.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Engine.h"
#include "Transform.h"
#include "Timer.h"

PlayerHealthBarShowScript::PlayerHealthBarShowScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

PlayerHealthBarShowScript::~PlayerHealthBarShowScript()
{
}

void PlayerHealthBarShowScript::LateUpdate()
{
	float fRatio = m_pPlayer.lock()->GetStatus()->GetHPRatio();

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());
	
	const Vec3& vParentPos = GetTransform()->GetParent().lock()->GetLocalPosition();
	const Vec3& vMyPos = vParentPos + GetTransform()->GetLocalPosition();

	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	GetMeshRenderer()->GetMaterial()->SetVec2(0, Vec2(900.f, 8.f));
	GetMeshRenderer()->GetMaterial()->SetVec2(1, Vec2(fWidth / 1.25f, fHeight / 1.25f));
	GetMeshRenderer()->GetMaterial()->SetVec2(2, Vec2(vMyPos.x, vMyPos.y));
}
