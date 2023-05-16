#include "pch.h"
#include "Skul.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Transform.h"
#include "SkulSkill.h"
#include "InterfaceManager.h"
#include "SkillBoxHUD.h"
#include "SkulAttack.h"

Skul::Skul(const SkulInfo& skulInfo)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkulIndex(SKUL_INDEX::END)
	, m_bSkillActiveType(SKILL_TYPE::NONE)
	, m_iEnumIndex(0)
	, m_SkulInfo(skulInfo)
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
	SkulInfoUpdate();
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

void Skul::AddAttackAnimation(ATTACK_ORDER eAttackOrder, const wstring& szName, shared_ptr<Animation> pAnimation, uint8 iEnum)
{
	assert(GetAnimator());
	GetAnimator()->AddAnimation(szName, pAnimation);
	
	switch (eAttackOrder)
	{
	case ATTACK_ORDER::ATTACK_A:
		m_vStateToNameMaps[iEnum][PLAYER_STATE::ATTACK_A] = szName;
		break;
	case ATTACK_ORDER::ATTACK_B:
		m_vStateToNameMaps[iEnum][PLAYER_STATE::ATTACK_B] = szName;
		break;
	case ATTACK_ORDER::ATTACK_C:
		m_vStateToNameMaps[iEnum][PLAYER_STATE::ATTACK_C] = szName;
		break;
	case ATTACK_ORDER::ATTACK_D:
		m_vStateToNameMaps[iEnum][PLAYER_STATE::ATTACK_D] = szName;
		break;
	case ATTACK_ORDER::ATTACK_E:
		m_vStateToNameMaps[iEnum][PLAYER_STATE::ATTACK_E] = szName;
		break;
	}
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

void Skul::PlayAnimation(ATTACK_ORDER eAttackOrder, bool bLoop, int32 iSection)
{
	assert(GetAnimator());
	wstring szName = {};

	switch (eAttackOrder)
	{
	case ATTACK_ORDER::ATTACK_A:
		szName = GetStateToName(PLAYER_STATE::ATTACK_A);
		break;
	case ATTACK_ORDER::ATTACK_B:
		szName = GetStateToName(PLAYER_STATE::ATTACK_B);
		break;
	case ATTACK_ORDER::ATTACK_C:
		szName = GetStateToName(PLAYER_STATE::ATTACK_C);
		break;
	case ATTACK_ORDER::ATTACK_D:
		szName = GetStateToName(PLAYER_STATE::ATTACK_D);
		break;
	case ATTACK_ORDER::ATTACK_E:
		szName = GetStateToName(PLAYER_STATE::ATTACK_E);
		break;
	}

	assert(!szName.empty());
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

		if (pSkulSkill->GetAnimation().lock())
		{
			const wstring& szName = pSkulSkill->GetAnimationName();
			GetAnimator()->AddAnimation(szName, pSkulSkill->GetAnimation().lock());
		}

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
				CooldownCompletion(static_cast<SKILL_INDEX>(i));
			}
		}
	}
}

void Skul::RefreshAnimation()
{
	m_pPlayer.lock()->RefreshAnimation();
}

void Skul::SetAttackMethod(shared_ptr<SkulAttack> pAttackMethod)
{
	assert(pAttackMethod);

	auto& attackInfo = pAttackMethod->m_arrAttackInfo;
	for (int32 i = 0; i < attackInfo.size(); ++i)
	{
		for (int32 j = 0; j < ATTACK_ORDER_COUNT; ++j)
		{
			if (attackInfo[i][j].pAnimation)
			{
				AddAttackAnimation(static_cast<ATTACK_ORDER>(j), attackInfo[i][j].pAnimation->GetName(), attackInfo[i][j].pAnimation, attackInfo[i][j].iEnum);
			}
		}
	}

	m_pAttackMethod = pAttackMethod;
}

SKILL_INDEX Skul::GetTotalSkills()
{
	if (m_arrSkills[static_cast<uint8>(SKILL_INDEX::SECOND)])
		return SKILL_INDEX::SECOND;
	else
		return SKILL_INDEX::FIRST;
}

const SkulInfo& Skul::GetSkulInfo()
{
	SkulInfoUpdate();
	return m_SkulInfo;
}

void Skul::SkulInfoUpdate()
{
	SKILL_INDEX eSkillIndex = GetTotalSkills();

	switch (eSkillIndex)
	{
	case SKILL_INDEX::FIRST:
		m_SkulInfo.FirstSkillInfo = GetSkill(SKILL_INDEX::FIRST).lock()->GetSkillInfo();
		break;
	case SKILL_INDEX::SECOND:
		m_SkulInfo.FirstSkillInfo = GetSkill(SKILL_INDEX::FIRST).lock()->GetSkillInfo();
		m_SkulInfo.SecondSkillInfo = GetSkill(SKILL_INDEX::SECOND).lock()->GetSkillInfo();
		break;
	}

	m_SkulInfo.SwapSkillInfo = GetSwapSkill().lock()->GetSkillInfo();
}

void Skul::CooldownCompletion(SKILL_INDEX eSkillIndex)
{
	switch (eSkillIndex)
	{
	case SKILL_INDEX::FIRST:
	{
		weak_ptr<Interface> pInterface = GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_FIRST);
		assert(pInterface.lock());
		static_pointer_cast<SkillBoxHUD>(pInterface.lock())->PlayCompletionAnimation();
	}
	break;
	case SKILL_INDEX::SECOND:
	{
		weak_ptr<Interface> pInterface = GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::PLAYER_SKILL_BOX_SECOND);
		assert(pInterface.lock());
		static_pointer_cast<SkillBoxHUD>(pInterface.lock())->PlayCompletionAnimation();
	}
		break;
	}

	CooldownCompletionCallback(eSkillIndex);
}



weak_ptr<Animation> Skul::GetActiveAnimation()
{
	assert(GetAnimator());
	assert(GetAnimator()->GetActiveAnimation());
	return GetAnimator()->GetActiveAnimation();
}

