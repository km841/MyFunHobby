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
		pLittleBone->AddComponent(make_shared<Transform>());

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\LittleBone\\littlebone_idle.anim");
		shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\LittleBone\\littlebone_walk.anim");
		shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Dash", L"..\\Resources\\Animation\\LittleBone\\littlebone_dash.anim");
		shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_rise.anim");
		shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_fall.anim");
		shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpAttack", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_attack.anim");
		shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackA", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_a.anim");
		shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackB", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_b.anim");

		pLittleBone->AddAnimation(PLAYER_STATE::IDLE, L"LittleBone_Idle", pIdleAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::WALK, L"LittleBone_Walk", pWalkAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::DASH, L"LittleBone_Dash", pDashAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::JUMP_RISE, L"LittleBone_JumpRise", pJumpRiseAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::JUMP_FALL, L"LittleBone_JumpFall", pJumpFallAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"LittleBone_JumpAttack", pJumpAttackAnimation);
		pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_A, L"LittleBone_AttackA", pAttackA_Animation);
		pLittleBone->AddAnimation(PLAYER_STATE::ATTACK_B, L"LittleBone_AttackB", pAttackB_Animation);

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
