#include "pch.h"
#include "PlayerSkillShowScript.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animator.h"
#include "Animation.h"
#include "SkillBoxHUD.h"
#include "InterfaceEffect.h"
#include "InterfaceManager.h"

PlayerSkillShowScript::PlayerSkillShowScript(shared_ptr<SkillBoxHUD> pHUD, SKILL_INDEX eSkillIndex)
	: m_pHUD(pHUD)
	, m_eSkillIndex(eSkillIndex)
	, m_bFlag(false)
	, m_bPrevFlag(true)
{
}

PlayerSkillShowScript::~PlayerSkillShowScript()
{
}

void PlayerSkillShowScript::LateUpdate()
{
	weak_ptr<SkulSkill> pSkill = m_pHUD.lock()->GetPlayer().lock()->GetActiveSkul()->GetSkill(m_eSkillIndex);
	if (pSkill.lock())
	{
		if (SKILL_INDEX::SECOND == m_eSkillIndex)
			GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SECOND_SKILL_FRAME)->Enable();

		m_bFlag = pSkill.lock()->IsActive();
		float fCooldownProgress = pSkill.lock()->GetCooldownProgress();
		bool bActive = m_bFlag;
		weak_ptr<Texture> pTexture = pSkill.lock()->GetSkillTexture().lock();

		GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture.lock());
		GetMeshRenderer()->GetMaterial()->SetFloat(0, fCooldownProgress);
		GetMeshRenderer()->GetMaterial()->SetInt(3, static_cast<int32>(bActive));
	}
	else
	{
		if (SKILL_INDEX::SECOND == m_eSkillIndex)
			GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SECOND_SKILL_FRAME)->Disable();
	}
}
