#include "pch.h"
#include "PlayerFirstSkillShowScript.h"
#include "Skul.h"
#include "SkulSkill.h"
#include "Player.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animator.h"
#include "Animation.h"

PlayerFirstSkillShowScript::PlayerFirstSkillShowScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
	, m_bFlag(false)
	, m_bPrevFlag(true)
	, m_bAnimationFlag(false)
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
			m_bAnimationFlag = true;
			// 
			// Animation Play 하면 자동으로 Animation Flag가 넘어간다.
			// 애니메이션이 끝날 때까지 애니메이션 전달
			
			//GetAnimator()->Play(L"", false);
			// 처음 2프레임은 기존 텍스쳐와 겹쳐서 출력된다.
		}

		if (m_bAnimationFlag)
		{
			


		}

		

		// 쿨타임이 완료된 시점이라면? 애니메이션 출력
		//1. 텍스쳐 1번 인덱스로 빛 텍스쳐를 전달한다



		m_bPrevFlag = m_bFlag;
	}
}
