#include "pch.h"
#include "Skul.h"
#include "Animator.h"
#include "Animation.h"

Skul::Skul(SKUL_GRADE eSkulGrade)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkulPos(SKUL_POS::FIRST)
	, m_eSkulGrade(eSkulGrade)
{
}

void Skul::AddAnimation(PLAYER_STATE ePlayerState, const wstring& szName, shared_ptr<Animation> pAnimation)
{
	assert(GetAnimator());
	GetAnimator()->AddAnimation(szName, pAnimation);
	m_mStateToKeyMap[ePlayerState] = szName;
}

const wstring& Skul::GetStateToKey(PLAYER_STATE ePlayerState)
{
	auto iter = m_mStateToKeyMap.find(ePlayerState);
	assert(iter != m_mStateToKeyMap.end());
	return iter->second;
}
