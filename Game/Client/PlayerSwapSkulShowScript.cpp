#include "pch.h"
#include "PlayerSwapSkulShowScript.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"
#include "Skul.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "HUD.h"

PlayerSwapSkulShowScript::PlayerSwapSkulShowScript()
{
}

PlayerSwapSkulShowScript::~PlayerSwapSkulShowScript()
{
}

void PlayerSwapSkulShowScript::LateUpdate()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
	if (!pPlayer.lock()->GetSkul(SKUL_INDEX::SECOND).lock())
	{
		GetGameObject()->Disable();
		return;
	}

	SKUL_INDEX eSkulIndex = pPlayer.lock()->GetActiveSkul()->GetSkulIndex();
	switch (eSkulIndex)
	{
	case SKUL_INDEX::FIRST:
	{
		weak_ptr<Texture> pTexture = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetSkul(SKUL_INDEX::SECOND).lock()->GetThumnailImage().lock();
		GetGameObject()->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture.lock());
	}
		break;
	case SKUL_INDEX::SECOND:
	{
		weak_ptr<Texture> pTexture = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetSkul(SKUL_INDEX::FIRST).lock()->GetThumnailImage().lock();
		GetGameObject()->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture.lock());
	}
		break;
	}
}
