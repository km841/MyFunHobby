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
#include "Texture.h"
#include "HighWarlock.h"
#include "HighWarlockSwapSkill.h"
#include "LittleBoneSwapSkill.h"
#include "AbyssMeteorSkill.h"
#include "HighWarlockChargingScript.h"
#include "LittleBoneAttack.h"
#include "HighWarlockAttack.h"
#include "AbyssOrbSkill.h"
#include "DevilBerserker.h"
#include "DevilBerserkerAttack.h"
#include "DevilBerserkerSwapSkill.h"
#include "BoneHawlSkill.h"
#include "RageTackleSkill.h"
#include "SoundListener.h"
#include "SoundSource.h"


void Cemetery::Init()
{
	CreateSkul();
}

shared_ptr<Skul> Cemetery::Get(SKUL_KIND eSkulType)
{
	auto iter = m_mSkulMap.find(eSkulType);
	assert(iter != m_mSkulMap.end());
	return iter->second;
}

const SkulInfo& Cemetery::GetSkulInfo(SKUL_KIND eSkulKind)
{
	auto iter = m_mSkulInfoMap.find(eSkulKind);
	assert(iter != m_mSkulInfoMap.end());
	return iter->second;
}

void Cemetery::Destroy()
{
	for (auto pSkul : m_mSkulMap)
		pSkul.second.reset();
}

void Cemetery::CreateSkul()
{
	// LittleBone
	{
		SkulInfo skulInfo = {};
		skulInfo.szName = L"리틀 본";
		skulInfo.eGrade = GRADE::NORMAL;
		skulInfo.eSkulKind = SKUL_KIND::LITTLE_BONE;
		skulInfo.eSkulType = SKUL_TYPE::BALANCE;
		skulInfo.szComment = L"마왕성 경비대의 막내 스켈레톤.\n다른 스켈레톤에 비해 체구가 작아 리틀본이라 불린다.";
		skulInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"LittleBone_Vignette", L"..\\Resources\\Texture\\Sprites\\LittleBone\\Image_LittleBone_Vignette.png");
		m_mSkulInfoMap[SKUL_KIND::LITTLE_BONE] = skulInfo;

		shared_ptr<LittleBone> pLittleBone = make_shared<LittleBone>(skulInfo);
		pLittleBone->AddComponent(make_shared<Animator>());
		//pLittleBone->AddComponent(make_shared<SoundListener>());
		pLittleBone->AddComponent(make_shared<SoundSource>());
		
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pLittleBone->AddComponent(pMeshRenderer);
		pLittleBone->AddComponent(make_shared<Transform>());
		pLittleBone->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

		uint8 iHasHeadEnum = static_cast<uint8>(LITTLE_BONE_STATE::HAS_HEAD);
		// Has Head Animation
		{
			shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Idle", L"..\\Resources\\Animation\\LittleBone\\littlebone_idle.anim");
			shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Walk", L"..\\Resources\\Animation\\LittleBone\\littlebone_walk.anim");
			shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_Dash", L"..\\Resources\\Animation\\LittleBone\\littlebone_dash.anim");
			shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpRise", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_rise.anim");
			shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpFall", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_fall.anim");
			shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_JumpAttack", L"..\\Resources\\Animation\\LittleBone\\littlebone_jump_attack.anim");


			pLittleBone->AddAnimation(PLAYER_STATE::IDLE, L"LittleBone_Idle", pIdleAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::WALK, L"LittleBone_Walk", pWalkAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::DASH, L"LittleBone_Dash", pDashAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_RISE, L"LittleBone_JumpRise", pJumpRiseAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_FALL, L"LittleBone_JumpFall", pJumpFallAnimation, iHasHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"LittleBone_JumpAttack", pJumpAttackAnimation, iHasHeadEnum);
			//pLittleBone->AddAnimation(PLAYER_STATE::ATTACK, L"LittleBone_AttackA", pAttackA_Animation, iHasHeadEnum);
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

			pLittleBone->AddAnimation(PLAYER_STATE::IDLE, L"LittleBone_NoHead_Idle", pIdleAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::WALK, L"LittleBone_NoHead_Walk", pWalkAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::DASH, L"LittleBone_NoHead_Dash", pDashAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_RISE, L"LittleBone_NoHead_JumpRise", pJumpRiseAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_FALL, L"LittleBone_NoHead_JumpFall", pJumpFallAnimation, iNoHeadEnum);
			pLittleBone->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"LittleBone_NoHead_JumpAttack", pJumpAttackAnimation, iNoHeadEnum);
		}

		// LittleBone Attack Method
		{
			shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackA", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_a.anim");
			shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_AttackB", L"..\\Resources\\Animation\\LittleBone\\littlebone_attack_b.anim");

			shared_ptr<Animation> pNoHead_AttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_AttackA", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_attack_a.anim");
			shared_ptr<Animation> pNoHead_AttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"LittleBone_NoHead_AttackB", L"..\\Resources\\Animation\\LittleBone\\nohead_littlebone_attack_b.anim");

			pAttackA_Animation->SetHitFrame(1);
			pAttackB_Animation->SetHitFrame(1);
			pNoHead_AttackA_Animation->SetHitFrame(1);
			pNoHead_AttackB_Animation->SetHitFrame(1);

			shared_ptr<LittleBoneAttack> pLittleBoneAttackMethod = make_shared<LittleBoneAttack>(pLittleBone);
			pLittleBoneAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_A, AttackInfo{ pAttackA_Animation , -20.f, 90.f, 150.f, iHasHeadEnum });
			pLittleBoneAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_A, AttackInfo{ pNoHead_AttackA_Animation , -20.f, 90.f, 150.f, iNoHeadEnum });
			pLittleBoneAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_B, AttackInfo{ pAttackB_Animation , -20.f, 90.f, 150.f, iHasHeadEnum });
			pLittleBoneAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_B, AttackInfo{ pNoHead_AttackB_Animation , -20.f, 90.f, 150.f, iNoHeadEnum });

			pLittleBone->SetAttackMethod(pLittleBoneAttackMethod);
		}
		// Skull Throw Skill
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 6.f;
			skillInfo.fDuration = 0.25f;
			skillInfo.pSkillTexture = GET_SINGLE(Resources)->Load<Texture>(L"LittleBone_Throw", L"..\\Resources\\Texture\\HUD\\LittleBone\\HUD_SkullThrow.tga");
			skillInfo.szComment = L"자신의 머리를 던져 마법 데미지를 입힙니다.\n던진 머리를 회수하면 쿨타임이 초기화됩니다.";
			skillInfo.szName = L"두개골 투척";

			shared_ptr<SkullThrowSkill> pThrowSkill = make_shared<SkullThrowSkill>(skillInfo);

			wstring szAnimationName = L"LittleBone_Throw";
			pThrowSkill->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pThrowAnimation = GET_SINGLE(Resources)->Load<Animation>(szAnimationName, L"..\\Resources\\Animation\\LittleBone\\littlebone_throw.anim");
			pThrowSkill->SetAnimation(pThrowAnimation);

			pLittleBone->ObtainSkill(pThrowSkill);
		}

		// LittleBone Swap Skill
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 0.f;
			skillInfo.fDuration = 2.f;
			skillInfo.szComment = L"교대 시 뼈를 들고 회전해 물리 데미지를 입힙니다.";
			skillInfo.szName = L"바톤 터치";

			shared_ptr<LittleBoneSwapSkill> pSwapSkill = make_shared<LittleBoneSwapSkill>(skillInfo);

			wstring szAnimationName = L"LittleBone_Swap";
			pSwapSkill->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pSwapAnimation = GET_SINGLE(Resources)->Load<Animation>(szAnimationName, L"..\\Resources\\Animation\\LittleBone\\littlebone_swap.anim");
			pSwapSkill->SetAnimation(pSwapAnimation);

			pLittleBone->SetSwapSkill(pSwapSkill);
		}

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"LittleBone_Thumnail", L"..\\Resources\\Texture\\HUD\\LittleBone\\Image_LittleBone_Thumnail.tga");
		pLittleBone->SetThumnailImage(pTexture);

		m_mSkulMap[SKUL_KIND::LITTLE_BONE] = pLittleBone;
	}



	// High Warlock
	{
		SkulInfo skulInfo = {};
		skulInfo.szName = L"대마도사";
		skulInfo.eGrade = GRADE::UNIQUE;
		skulInfo.eSkulKind = SKUL_KIND::HIGH_WARLOCK;
		skulInfo.eSkulType = SKUL_TYPE::BALANCE;
		skulInfo.szComment = L"마나의 흐름을 느끼는데 살가죽은 방해가 될 뿐이다.\n- 마왕성 제 1 마도 군단장";
		skulInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"HighWarlock_Vignette", L"..\\Resources\\Texture\\Sprites\\HighWarlock\\Image_HighWarlock_Vignette.png");
		skulInfo.vVignetteTextureOffset = Vec2(5.f, 20.f);
		m_mSkulInfoMap[SKUL_KIND::HIGH_WARLOCK] = skulInfo;

		shared_ptr<HighWarlock> pHighWarlock = make_shared<HighWarlock>(skulInfo);
		pHighWarlock->AddComponent(make_shared<Animator>());
		//pHighWarlock->AddComponent(make_shared<SoundListener>());
		pHighWarlock->AddComponent(make_shared<SoundSource>());

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();
		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pHighWarlock->AddComponent(pMeshRenderer);
		pHighWarlock->AddComponent(make_shared<Transform>());
		pHighWarlock->AddComponent(make_shared<HighWarlockChargingScript>(pHighWarlock));
		pHighWarlock->GetTransform()->SetGlobalOffset(Vec2(0.f, 30.f));

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Idle", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_idle.anim");
		shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Walk", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_walk.anim");
		shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Walk", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_dash.anim");
		shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_JumpRise", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_jump_rise.anim");
		shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_JumpFall", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_jump_fall.anim");
		shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_JumpAttack", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_jump_attack.anim");
		
		shared_ptr<Animation> pCharging_Animation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_Charging", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_charging.anim");

		pHighWarlock->AddAnimation(PLAYER_STATE::IDLE, L"HighWarlock_Idle", pIdleAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::WALK, L"HighWarlock_Walk", pWalkAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::DASH, L"HighWarlock_Dash", pDashAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::JUMP_RISE, L"HighWarlock_JumpRise", pJumpRiseAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::JUMP_FALL, L"HighWarlock_JumpFall", pJumpFallAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"HighWarlock_JumpAttack", pJumpAttackAnimation);
		pHighWarlock->AddAnimation(PLAYER_STATE::CHARGING, L"HighWarlock_Charging", pCharging_Animation);

		// HighWarlock Attack Method
		{
			shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_AttackA", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_attack_a.anim");
			shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"HighWarlock_AttackB", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_attack_b.anim");

			pAttackA_Animation->SetTriggerFrame(3);
			pAttackA_Animation->SetTriggerFrame(4);
			pAttackA_Animation->SetTriggerFrame(5);
			pAttackB_Animation->SetTriggerFrame(1);
			pAttackB_Animation->SetTriggerFrame(2);
			pAttackB_Animation->SetTriggerFrame(3);

			shared_ptr<HighWarlockAttack> pHighWarlockAttackMethod = make_shared<HighWarlockAttack>(pHighWarlock);
			pHighWarlockAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_A, AttackInfo{ pAttackA_Animation , -20.f, 90.f, 100.f });
			pHighWarlockAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_B, AttackInfo{ pAttackB_Animation , -20.f, 90.f, 100.f });
	
			pHighWarlock->SetAttackMethod(pHighWarlockAttackMethod);
		}

		// HighWarlock Swap Skill
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 0.f;
			skillInfo.fDuration = 0.f;
			skillInfo.szComment = L"어비스 필드를 소환한다.";
			skillInfo.szName = L"어비스 필드";

			shared_ptr<HighWarlockSwapSkill> pSwapSkill = make_shared<HighWarlockSwapSkill>(skillInfo);
			pHighWarlock->SetSwapSkill(pSwapSkill);
		}

		// AbyssMeteor Skill
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::CHARGING;
			skillInfo.fCooldown = 5.f;
			skillInfo.fDuration = 0.5f;
			skillInfo.pSkillTexture = GET_SINGLE(Resources)->Load<Texture>(L"HighWarlock_AbyssMeteor", L"..\\Resources\\Texture\\HUD\\HighWarlock\\HUD_AbyssMeteor.png");
			skillInfo.szComment = L"메테오를 소환한다.";
			skillInfo.szName = L"어비스 메테오";

			shared_ptr<AbyssMeteorSkill> pAbyssMeteorSkill = make_shared<AbyssMeteorSkill>(skillInfo);

			wstring szAnimationName = L"HighWarlock_AbyssMeteor";
			pAbyssMeteorSkill->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(szAnimationName, L"..\\Resources\\Animation\\HighWarlock\\highwarlock_skill.anim");
			pAbyssMeteorSkill->SetAnimation(pAnimation);

			pHighWarlock->ObtainSkill(pAbyssMeteorSkill);
		}
		
		// Abyss Orb
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::CHARGING;
			skillInfo.fCooldown = 5.f;
			skillInfo.fDuration = 0.5f;
			skillInfo.pSkillTexture = GET_SINGLE(Resources)->Load<Texture>(L"HighWarlock_AbyssOrb", L"..\\Resources\\Texture\\HUD\\HighWarlock\\HUD_AbyssOrb.png");
			skillInfo.szComment = L"오브를 소환한다.";
			skillInfo.szName = L"어비스 오브";

			shared_ptr<AbyssOrbSkill> pAbyssOrbSkill = make_shared<AbyssOrbSkill>(skillInfo);

			wstring szAnimationName = L"HighWarlock_AbyssOrb";
			pAbyssOrbSkill->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(szAnimationName, L"..\\Resources\\Animation\\HighWarlock\\highwarlock_skill.anim");
			pAbyssOrbSkill->SetAnimation(pAnimation);

			pHighWarlock->ObtainSkill(pAbyssOrbSkill);
		}


		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HighWarlock_Thumnail", L"..\\Resources\\Texture\\HUD\\HighWarlock\\Image_HighWarlock_Thumnail.png");
		pHighWarlock->SetThumnailImage(pTexture);

		m_mSkulMap[SKUL_KIND::HIGH_WARLOCK] = pHighWarlock;
	}


	// Devil Berserker
	{
		SkulInfo skulInfo = {};
		skulInfo.szName = L"데빌 버서커";
		skulInfo.eGrade = GRADE::LEGENDARY;
		skulInfo.eSkulKind = SKUL_KIND::DEVIL_BERSERKER;
		skulInfo.eSkulType = SKUL_TYPE::POWER;
		skulInfo.szComment = L"강력한 힘을 위해 돌이킬 수 없는 계약을 맺었던 광기의 전사";
		skulInfo.vVignetteTextureOffset = Vec2(75.f, 30.f);
		skulInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"DevilBerserker_Vignette", L"..\\Resources\\Texture\\Sprites\\DevilBerserker\\Image_DevilBerserker_Vignette.png");
		m_mSkulInfoMap[SKUL_KIND::DEVIL_BERSERKER] = skulInfo;

		shared_ptr<DevilBerserker> pDevilBerserker = make_shared<DevilBerserker>(skulInfo);
		pDevilBerserker->AddComponent(make_shared<Animator>());
		//pDevilBerserker->AddComponent(make_shared<SoundListener>());
		pDevilBerserker->AddComponent(make_shared<SoundSource>());

		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred")->Clone();

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);

		pDevilBerserker->AddComponent(pMeshRenderer);
		pDevilBerserker->AddComponent(make_shared<Transform>());
		pDevilBerserker->GetTransform()->SetGlobalOffset(Vec2(0.f, 20.f));

		uint8 iNormalEnum = static_cast<uint8>(BERSERKER_STATE::NORMAL);
		// Normal Mode Animation
		{
			shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_Idle", L"..\\Resources\\Animation\\DevilBerserker\\berserker_idle.anim");
			shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_Walk", L"..\\Resources\\Animation\\DevilBerserker\\berserker_walk.anim");
			shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_Dash", L"..\\Resources\\Animation\\DevilBerserker\\berserker_dash.anim");
			shared_ptr<Animation> pLandAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_Land", L"..\\Resources\\Animation\\DevilBerserker\\berserker_land.anim");
			shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_JumpRise", L"..\\Resources\\Animation\\DevilBerserker\\berserker_jump_rise.anim");
			shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_JumpFall", L"..\\Resources\\Animation\\DevilBerserker\\berserker_jump_fall.anim");
			shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_JumpAttack", L"..\\Resources\\Animation\\DevilBerserker\\berserker_jump_attack.anim");


			pDevilBerserker->AddAnimation(PLAYER_STATE::IDLE, L"Berserker_Idle", pIdleAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::WALK, L"Berserker_Walk", pWalkAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::DASH, L"Berserker_Dash", pDashAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::LAND, L"Berserker_Land", pLandAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_RISE, L"Berserker_JumpRise", pJumpRiseAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_FALL, L"Berserker_JumpFall", pJumpFallAnimation, iNormalEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"Berserker_JumpAttack", pJumpAttackAnimation, iNormalEnum);
		}

		uint8 iDevilEnum = static_cast<uint8>(BERSERKER_STATE::DEVIL);
		// Devil Mode Animation
		{
			shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_Idle", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_idle.anim");
			shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_Walk", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_walk.anim");
			shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_Dash", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_dash.anim");
			shared_ptr<Animation> pLandAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_Land", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_land.anim");
			shared_ptr<Animation> pJumpRiseAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_JumpRise", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_jump_rise.anim");
			shared_ptr<Animation> pJumpFallAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_JumpFall", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_jump_fall.anim");
			shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_JumpAttack", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_jump_attack.anim");

			pDevilBerserker->AddAnimation(PLAYER_STATE::IDLE, L"DevilBerserker_Idle", pIdleAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::WALK, L"DevilBerserker_Walk", pWalkAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::DASH, L"DevilBerserker_Dash", pDashAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::LAND, L"DevilBerserker_Land", pLandAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_RISE, L"DevilBerserker_JumpRise", pJumpRiseAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_FALL, L"DevilBerserker_JumpFall", pJumpFallAnimation, iDevilEnum);
			pDevilBerserker->AddAnimation(PLAYER_STATE::JUMP_ATTACK, L"DevilBerserker_JumpAttack", pJumpAttackAnimation, iDevilEnum);
		}

		// Berserker Attack Method
		{
			shared_ptr<Animation> pAttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_AttackA", L"..\\Resources\\Animation\\DevilBerserker\\berserker_attack_a.anim");
			shared_ptr<Animation> pAttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"Berserker_AttackB", L"..\\Resources\\Animation\\DevilBerserker\\berserker_attack_b.anim");

			shared_ptr<Animation> pDevilMode_AttackA_Animation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_AttackA", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_attack_a.anim");
			shared_ptr<Animation> pDevilMode_AttackB_Animation = GET_SINGLE(Resources)->Load<Animation>(L"DevilBerserker_AttackB", L"..\\Resources\\Animation\\DevilBerserker\\devilberserker_attack_b.anim");

			pAttackA_Animation->SetHitFrame(4);
			pAttackB_Animation->SetHitFrame(4);
			pDevilMode_AttackA_Animation->SetHitFrame(3);
			pDevilMode_AttackB_Animation->SetHitFrame(2);

			shared_ptr<DevilBerserkerAttack> pDevilBerserkerAttackMethod = make_shared<DevilBerserkerAttack>(pDevilBerserker);
			pDevilBerserkerAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_A, AttackInfo{ pAttackA_Animation , -20.f, 90.f, 200.f, iNormalEnum });
			pDevilBerserkerAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_A, AttackInfo{ pDevilMode_AttackA_Animation , -20.f, 90.f, 200.f, iDevilEnum });
			pDevilBerserkerAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_B, AttackInfo{ pAttackB_Animation , -20.f, 90.f, 200.f, iNormalEnum });
			pDevilBerserkerAttackMethod->AddAttackInfo(ATTACK_ORDER::ATTACK_B, AttackInfo{ pDevilMode_AttackB_Animation , -20.f, 90.f, 200.f, iDevilEnum });

			pDevilBerserker->SetAttackMethod(pDevilBerserkerAttackMethod);
		}

		// DevilBerserker Swap Skill
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 0.f;
			skillInfo.fDuration = 2.f;
			skillInfo.szComment = L"교대 시 점프하여 적을 내려칩니다.";
			skillInfo.szName = L"내려 찍기";

			shared_ptr<DevilBerserkerSwapSkill> pSwapSkill = make_shared<DevilBerserkerSwapSkill>(skillInfo);
			pDevilBerserker->SetSwapSkill(pSwapSkill);
		}

		// DevilBerserker Demonization
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 30.f;
			skillInfo.fDuration = 2.5f;
			skillInfo.pSkillTexture = GET_SINGLE(Resources)->Load<Texture>(L"DevilBerserker_BoneHawl", L"..\\Resources\\Texture\\HUD\\DevilBerserker\\HUD_BoneHawl.png");
			skillInfo.szComment = L"현재 체력의 10%를 소모해 20초간 악마로 변하며 넓은 범위의 적에게 물리데미지를 입힙니다.";
			skillInfo.szName = L"악마의 뼈";

			shared_ptr<BoneHawlSkill> pBoneHawlSkill = make_shared<BoneHawlSkill>(skillInfo);

			wstring szAnimationName = L"DevilBerserker_Demonization";
			pBoneHawlSkill->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pSwapAnimation = GET_SINGLE(Resources)->LoadAnimation(szAnimationName, L"..\\Resources\\Animation\\DevilBerserker\\berserker_demonization.anim");
			pBoneHawlSkill->SetAnimation(pSwapAnimation);

			pDevilBerserker->ObtainSkill(pBoneHawlSkill);
		}

		// DevilBerserker RageTackle
		{
			SkillInfo skillInfo = {};
			skillInfo.eSkillType = SKILL_TYPE::INSTANT;
			skillInfo.fCooldown = 10.f;
			skillInfo.fDuration = 4.f;
			skillInfo.pSkillTexture = GET_SINGLE(Resources)->Load<Texture>(L"DevilBerserker_MadRush", L"..\\Resources\\Texture\\HUD\\DevilBerserker\\HUD_MadRush.png");
			skillInfo.szComment = L"버튼을 누르고 있으면 바라보는 방향으로 돌진하며,\n악마의 힘이 서린 참격을 가합니다";
			skillInfo.szName = L"레이지 태클";

			shared_ptr<RageTackleSkill> pRageTackle = make_shared<RageTackleSkill>(skillInfo);

			wstring szAnimationName = L"DevilBerserker_Temp";
			pRageTackle->SetAnimationName(szAnimationName);

			shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(szAnimationName, L"..\\Resources\\Animation\\DevilBerserker\\berserker_demonization.anim");
			pRageTackle->SetAnimation(pAnimation);

			pDevilBerserker->ObtainSkill(pRageTackle);
		}

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"DevilBerserker_Thumnail", L"..\\Resources\\Texture\\HUD\\DevilBerserker\\Image_DevilBerserker_Thumnail.png");
		pDevilBerserker->SetThumnailImage(pTexture);

		m_mSkulMap[SKUL_KIND::DEVIL_BERSERKER] = pDevilBerserker;
	}
}
