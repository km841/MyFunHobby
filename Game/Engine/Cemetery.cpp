#include "pch.h"
#include "Cemetery.h"
#include "LittleBone.h"
#include "Animator.h"
#include "Animation.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "SkullThrowSkill.h"
#include "ReturnHeadScript.h"


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
		
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pLittleBone->AddComponent(pMeshRenderer);
		pLittleBone->AddComponent(make_shared<ReturnHeadScript>(pLittleBone));
		pLittleBone->AddComponent(make_shared<Transform>());


		uint8 iHasHeadEnum = static_cast<uint8>(LITTLE_BONE_STATE::HAS_HEAD);
		// Has Head Animation
		{
			shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\LittleBone\\littlebone_idle.anim");
			shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\LittleBone\\littlebone_walk.anim");
			shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Dash", L"..\\Resources\\Animation\\LittleBone\\littlebone_dash.anim");
			shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_rise.anim");
			shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_fall.anim");
			shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpAttack", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_attack.anim");
			shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackA", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_a.anim");
			shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackB", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_b.anim");

			pLittleBone->AddAnimation(PLAYER_STATE::IDLE, L"LittleBone_Idle", pIdleAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::WALK, L"LittleBone_Walk", pWalkAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::DASH, L"LittleBone_Dash", pDashAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_RISE, L"LittleBone_JumpRise", pJumpRiseAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_FALL, L"LittleBone_JumpFall", pJumpFallAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"LittleBone_JumpAttack", pJumpAttackAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_A, L"LittleBone_AttackA", pAttackA_Animation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_B, L"LittleBone_AttackB", pAttackB_Animation, iHasHeadEnum);
		}

		uint8 iNoHeadEnum = static_cast<uint8>(LITTLE_BONE_STATE::NO_HEAD);
		// No Head Animation
		{
			shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_Idle", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_idle.anim");
			shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_Walk", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_walk.anim");
			shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_Dash", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_dash.anim");
			shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_JumpRise", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_jump_rise.anim");
			shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_JumpFall", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_jump_fall.anim");
			shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_JumpAttack", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_jump_attack.anim");
			shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_AttackA", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_attack_a.anim");
			shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_AttackB", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_attack_b.anim");

			pLittleBone->AddAnimation(PLAYER_STATE::IDLE, L"LittleBone_NoHead_Idle", pIdleAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::WALK, L"LittleBone_NoHead_Walk", pWalkAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::DASH, L"LittleBone_NoHead_Dash", pDashAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_RISE, L"LittleBone_NoHead_JumpRise", pJumpRiseAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_FALL, L"LittleBone_NoHead_JumpFall", pJumpFallAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"LittleBone_NoHead_JumpAttack", pJumpAttackAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_A, L"LittleBone_NoHead_AttackA", pAttackA_Animation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_B, L"LittleBone_NoHead_AttackB", pAttackB_Animation, iNoHeadEnum);
		}

		// Skull Throw Skill
		{
			shared_ptr<SkullThrowSkill> pThrowSkill = make_shared<SkullThrowSkill>();
			wstring szAnimationName = L"LittleBone_Throw";
			pThrowSkill->SetAnimationName(szAnimationName);
			shared_ptr<Animation> pThrowAnimation = GET_SINGLE(Resources)->Load<Animation>(szAnimationName, L"..\\Resources\\Animation\\LittleBone\\littlebone_throw.anim");
			pThrowSkill->SetAnimation(pThrowAnimation);

			pLittleBone->ObtainSkill(pThrowSkill);
		}

		m_mSkulMap[SKUL_TYPE::LITTLE_BONE] = pLittleBone;
	}
}
