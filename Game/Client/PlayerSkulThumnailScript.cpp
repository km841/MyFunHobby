#include "pch.h"
#include "PlayerSkulThumnailScript.h"
#include "Player.h"
#include "Skul.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "SkulThumnailHUD.h"


PlayerSkulThumnailScript::PlayerSkulThumnailScript(shared_ptr<Player> pPlayer, shared_ptr<SkulThumnailHUD> pSkulThumnailHUD)
	: m_pPlayer(pPlayer)
	, m_pSkulThumnailHUD(pSkulThumnailHUD)
{
}

PlayerSkulThumnailScript::~PlayerSkulThumnailScript()
{
}

void PlayerSkulThumnailScript::LateUpdate()
{
	m_pSkulThumnailHUD.lock()->GetMeshRenderer()->GetMaterial()->SetTexture(0, m_pPlayer.lock()->GetActiveSkul()->GetThumnailImage().lock());
}
