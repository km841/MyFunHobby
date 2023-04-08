#include "pch.h"
#include "PlayerSkulThumnailScript.h"
#include "Player.h"
#include "Skul.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "SkulHeadHUD.h"


PlayerSkulThumnailScript::PlayerSkulThumnailScript(shared_ptr<Player> pPlayer, shared_ptr<SkulHeadHUD> pSkulHeadHUD)
	: m_pPlayer(pPlayer)
	, m_pSkulHeadHUD(pSkulHeadHUD)
{
}

PlayerSkulThumnailScript::~PlayerSkulThumnailScript()
{
}

void PlayerSkulThumnailScript::LateUpdate()
{
	m_pSkulHeadHUD.lock()->GetMeshRenderer()->GetMaterial()->SetTexture(0, m_pPlayer.lock()->GetActiveSkul()->GetThumnailImage().lock());
}
