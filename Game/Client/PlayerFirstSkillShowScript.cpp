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
			// Animation Play �ϸ� �ڵ����� Animation Flag�� �Ѿ��.
			// �ִϸ��̼��� ���� ������ �ִϸ��̼� ����
			
			//GetAnimator()->Play(L"", false);
			// ó�� 2�������� ���� �ؽ��Ŀ� ���ļ� ��µȴ�.
		}

		if (m_bAnimationFlag)
		{
			


		}

		

		// ��Ÿ���� �Ϸ�� �����̶��? �ִϸ��̼� ���
		//1. �ؽ��� 1�� �ε����� �� �ؽ��ĸ� �����Ѵ�



		m_bPrevFlag = m_bFlag;
	}
}
