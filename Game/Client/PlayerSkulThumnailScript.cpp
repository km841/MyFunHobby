#include "pch.h"
#include "PlayerSkulThumnailScript.h"
#include "Player.h"
#include "Skul.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "SkulThumnailHUD.h"
#include "Texture.h"


PlayerSkulThumnailScript::PlayerSkulThumnailScript(shared_ptr<SkulThumnailHUD> pSkulThumnailHUD)
	: m_pSkulThumnailHUD(pSkulThumnailHUD)
{
}

PlayerSkulThumnailScript::~PlayerSkulThumnailScript()
{
}

void PlayerSkulThumnailScript::LateUpdate()
{
	shared_ptr<Texture> pTexture = m_pSkulThumnailHUD.lock()->GetPlayer().lock()->GetActiveSkul()->GetThumnailImage().lock();
	float fCooldownProgress = m_pSkulThumnailHUD.lock()->GetPlayer().lock()->GetSwapCooldownProgress();
	bool bPossible = m_pSkulThumnailHUD.lock()->GetPlayer().lock()->IsSwapPossible();

	m_pSkulThumnailHUD.lock()->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
	GetMeshRenderer()->GetMaterial()->SetFloat(0, fCooldownProgress);
	GetMeshRenderer()->GetMaterial()->SetInt(3, static_cast<int32>(bPossible));
}
