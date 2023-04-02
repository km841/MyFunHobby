#include "pch.h"
#include "PlayerFirstSkillShowScript.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"

PlayerFirstSkillShowScript::PlayerFirstSkillShowScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

PlayerFirstSkillShowScript::~PlayerFirstSkillShowScript()
{
}

void PlayerFirstSkillShowScript::LateUpdate()
{
	weak_ptr<SkulSkill> pFirstSkill = m_pPlayer.lock()->GetActiveSkul()->GetSkill(SKILL_INDEX::FIRST);
	if (pFirstSkill.lock())
	{
		float fCooldownProgress = pFirstSkill.lock()->GetCooldownProgress();
		bool bActive = pFirstSkill.lock()->IsActive();
		weak_ptr<Texture> pTexture = pFirstSkill.lock()->GetTexture().lock();

		GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture.lock());
		GetMeshRenderer()->GetMaterial()->SetFloat(0, fCooldownProgress);
		GetMeshRenderer()->GetMaterial()->SetInt(0, static_cast<int32>(bActive));

	}
}
