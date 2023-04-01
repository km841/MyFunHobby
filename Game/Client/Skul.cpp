#include "pch.h"
#include "Skul.h"
#include "Animator.h"
#include "Animation.h"
#include "Player.h"
#include "Transform.h"

Skul::Skul(SKUL_GRADE eSkulGrade)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkulIndex(SKUL_INDEX::END)
	, m_eSkulGrade(eSkulGrade)
	, m_bSkillActiveFlag(false)
{
}

void Skul::SetPlayer(shared_ptr<Player> pPlayer)
{
	assert(pPlayer);
	GetTransform()->SetParent(pPlayer->GetTransform());
	m_pPlayer = pPlayer;
}

void Skul::AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation)
{
	assert(GetAnimator());
	GetAnimator()->AddAnimation(szName, pAnimation);
	m_mStateToNameMap[ePlayerState] = szName;
}

const wstring& Skul::GetStateToName(PLAYER_STATE ePlayerState)
{
	auto iter = m_mStateToNameMap.find(ePlayerState);
	assert(iter != m_mStateToNameMap.end());
	return iter->second;
}

void Skul::PlayAnimation(PLAYER_STATE ePlayerState, bool bLoop, int32 iSection)
{
	assert(GetAnimator());
	const wstring& szName = GetStateToName(ePlayerState);
	assert(GetAnimator()->FindAnimation(szName));
	GetAnimator()->Play(szName, bLoop, iSection);
}

void Skul::SetActiveSkill(SKILL_INDEX eSkillIndex)
{
	assert(m_arrSkills[static_cast<uint8>(eSkillIndex)]);
	m_pActiveSkill = m_arrSkills[static_cast<uint8>(eSkillIndex)];
}

shared_ptr<Animation> Skul::GetActiveAnimation()
{
	assert(GetAnimator());
	assert(GetAnimator()->GetActiveAnimation());
	return GetAnimator()->GetActiveAnimation();
}
