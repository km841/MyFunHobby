#include "pch.h"
#include "Skul.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Transform.h"
#include "SkulSkill.h"

Skul::Skul(SKUL_GRADE eSkulGrade)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkulIndex(SKUL_INDEX::END)
	, m_eSkulGrade(eSkulGrade)
	, m_bSkillActiveFlag(false)
	, m_iEnumIndex(0)
{
	m_vStateToNameMaps.resize(MAX_ENUMS);
}

void Skul::Awake()
{
	GameObject::Awake();
}

void Skul::Start()
{
	GameObject::Start();
}

void Skul::Update()
{
	GameObject::Update();
	SkillCooldownUpdate();
}

void Skul::LateUpdate()
{
	GameObject::LateUpdate();
}

void Skul::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Skul::SetPlayer(shared_ptr<Player> pPlayer)
{
	assert(pPlayer);
	GetTransform()->SetParent(pPlayer->GetTransform());
	m_pPlayer = pPlayer;
}

void Skul::AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation, uint8 iEnum)
{
	assert(GetAnimator());
	GetAnimator()->AddAnimation(szName, pAnimation);
	m_vStateToNameMaps[iEnum][ePlayerState] = szName;
}

const wstring& Skul::GetStateToName(PLAYER_STATE ePlayerState)
{
	auto iter = m_vStateToNameMaps[m_iEnumIndex].find(ePlayerState);
	assert(iter != m_vStateToNameMaps[m_iEnumIndex].end());
	return iter->second;
}

void Skul::PlayAnimation(PLAYER_STATE ePlayerState, bool bLoop, int32 iSection)
{
	assert(GetAnimator());

	const wstring& szName = GetStateToName(ePlayerState);
	assert(GetAnimator()->FindAnimation(szName));
	GetAnimator()->Play(szName, bLoop, iSection);
}

void Skul::PlayAnimation(const wstring& szName, bool bLoop, int32 iSection)
{
	assert(GetAnimator());
	assert(GetAnimator()->FindAnimation(szName));
	GetAnimator()->Play(szName, bLoop, iSection);
}

void Skul::SetActiveSkill(SKILL_INDEX eSkillIndex)
{
	assert(m_arrSkills[static_cast<uint8>(eSkillIndex)]);
	m_pActiveSkill = m_arrSkills[static_cast<uint8>(eSkillIndex)];
}

void Skul::ObtainSkill(shared_ptr<SkulSkill> pSkulSkill)
{
	assert(pSkulSkill);
	if (!m_arrSkills[static_cast<uint8>(SKILL_INDEX::FIRST)])
	{
		pSkulSkill->SetSkul(Conv::BaseToDeclare<Skul>(shared_from_this()));
		const wstring& szName = pSkulSkill->GetAnimationName();
		GetAnimator()->AddAnimation(szName, pSkulSkill->GetAnimation().lock());

		m_arrSkills[static_cast<uint8>(SKILL_INDEX::FIRST)] = pSkulSkill;
		m_arrSkills[static_cast<uint8>(SKILL_INDEX::FIRST)]->SetSkillIndex(SKILL_INDEX::FIRST);


	}
	else if (!m_arrSkills[static_cast<uint8>(SKILL_INDEX::SECOND)])
	{
		pSkulSkill->SetSkul(Conv::BaseToDeclare<Skul>(shared_from_this()));
		const wstring& szName = pSkulSkill->GetAnimationName();
		GetAnimator()->AddAnimation(szName, pSkulSkill->GetAnimation().lock());

		m_arrSkills[static_cast<uint8>(SKILL_INDEX::SECOND)] = pSkulSkill;
		m_arrSkills[static_cast<uint8>(SKILL_INDEX::SECOND)]->SetSkillIndex(SKILL_INDEX::SECOND);
	}
	else
		assert(nullptr);
}

void Skul::SetSwapSkill(shared_ptr<SkulSkill> pSwapSkill)
{
	assert(pSwapSkill);
	m_pSwapSkill = pSwapSkill;
	m_pSwapSkill->SetSkul(Conv::BaseToDeclare<Skul>(shared_from_this()));

	if (pSwapSkill->GetAnimation().lock())
	{
		const wstring& szName = pSwapSkill->GetAnimationName();
		GetAnimator()->AddAnimation(szName, pSwapSkill->GetAnimation().lock());
	}

}

void Skul::SkillCooldownUpdate()
{
	for (int32 i = 0; i < MAX_SKILLS; ++i)
	{
		if (m_arrSkills[i] && !m_arrSkills[i]->IsActive())
		{
			m_arrSkills[i]->UpdateSkillCooldown();
			if (m_arrSkills[i]->IsActive())
			{
				// Callback
				CooldownCompletionCallback(static_cast<SKILL_INDEX>(i));
			}
		}
	}
}

void Skul::RefreshAnimation()
{
	m_pPlayer.lock()->RefreshAnimation();
}

weak_ptr<Animation> Skul::GetActiveAnimation()
{
	assert(GetAnimator());
	assert(GetAnimator()->GetActiveAnimation());
	return GetAnimator()->GetActiveAnimation();
}

