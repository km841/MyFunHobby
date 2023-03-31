#include "pch.h"
#include "Cemetery.h"
#include "LittleBone.h"
#include "Animator.h"
#include "Animation.h"
#include "Resources.h"

void Cemetery::Init()
{
	CreateSkul();
}

shared_ptr<Skul> Cemetery::Get(SKUL_TYPE eSkulType)
{
	auto iter = m_mSkulMap.find(eSkulType);
	assert(iter != m_mSkulMap.end());
	return iter->second;
}

void Cemetery::CreateSkul()
{
	// LittleBone
	{
		shared_ptr<LittleBone> pLittleBone = make_shared<LittleBone>();
		pLittleBone->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\LittleBone\\littlebone_idle.anim");
		shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\LittleBone\\littlebone_walk.anim");
		shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Dash", L"..\\Resources\\Animation\\LittleBone\\littlebone_dash.anim");
		shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_rise.anim");
		shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_fall.anim");
		shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpAttack", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_attack.anim");
		shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackA", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_a.anim");
		shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackB", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_b.anim");

		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_Idle", pIdleAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_Walk", pWalkAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_Dash", pDashAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_JumpRise", pJumpRiseAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_JumpFall", pJumpFallAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_JumpAttack", pJumpAttackAnimation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_AttackA", pAttackA_Animation);
		pLittleBone->GetAnimator()->AddAnimation(L"LittleBone_AttackB", pAttackB_Animation);

		m_mSkulMap[SKUL_TYPE::LITTLE_BONE] = pLittleBone;
	}
}
