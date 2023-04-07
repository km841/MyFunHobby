#include "pch.h"
#include "PlayerFirstSkillShowScript.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animator.h"
#include "Animation.h"
#include "SkillBoxHUD.h"
#include "InterfaceEffect.h"

PlayerFirstSkillShowScript::PlayerFirstSkillShowScript(shared_ptr<Player> pPlayer, shared_ptr<SkillBoxHUD> pHUD)
	: m_pPlayer(pPlayer)
	, m_pHUD(pHUD)
	, m_bFlag(false)
	, m_bPrevFlag(true)
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
		m_bFlag = pFirstSkill.lock()->IsActive();
		float fCooldownProgress = pFirstSkill.lock()->GetCooldownProgress();
		bool bActive = m_bFlag;
		weak_ptr<Texture> pTexture = pFirstSkill.lock()->GetTexture().lock();

		GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture.lock());
		GetMeshRenderer()->GetMaterial()->SetFloat(0, fCooldownProgress);
		GetMeshRenderer()->GetMaterial()->SetInt(3, static_cast<int32>(bActive));

		if (!m_bPrevFlag && (m_bPrevFlag != m_bFlag))
		{
			m_pHUD.lock()->GetCompletionEffect().lock()->Enable();
			m_pHUD.lock()->GetCompletionEffect().lock()->GetAnimator()->Play(L"Cooldown_Completion", false);

		}
		else
		{
			if (m_pHUD.lock()->GetCompletionEffect().lock()->GetAnimator()->GetActiveAnimation())
			{
				if (m_pHUD.lock()->GetCompletionEffect().lock()->GetAnimator()->GetActiveAnimation()->IsFinished())
					m_pHUD.lock()->GetCompletionEffect().lock()->Disable();
			}

		}





		m_bPrevFlag = m_bFlag;
	}
}
