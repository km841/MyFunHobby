#include "pch.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"
#include "PlayerChangeStateEvent.h"
#include "Sequence.h"
#include "Selector.h"
#include "AI.h"
#include "Animator.h"
#include "Animation.h"
#include "AnimationLocalEffect.h"

/* Behavior Component */
#include "IsPlayerNearCondition.h"
#include "BehaviorTask.h"
#include "Sequence.h"
#include "MoveTask.h"
#include "RunAnimateTask.h"
#include "Selector.h"
#include "DelayTask.h"
#include "IsHitCondition.h"
#include "IsDeadCondition.h"
#include "RemoveObjectTask.h"
#include "IsPlayerInAttackRangeCondition.h"
#include "PlayerHitTask.h"


/* Engrave */
#include "Rapidity.h"
#include "Arms.h"

shared_ptr<Monster> ObjectFactory::CreateJuniorKnight(const Vec3& vMonsterPos)
{
	shared_ptr<JuniorKnight> pJuniorKnight = CreateObjectHasPhysicalFromPool<JuniorKnight>(L"Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
	pJuniorKnight->AddComponent(make_shared<AI>());
	pJuniorKnight->AddComponent(make_shared<Animator>());
	pJuniorKnight->AddComponent(make_shared<Movement>());

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\JuniorKnight\\";
	std::vector<wstring> vTextureNames;
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_1.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_2.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_3.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_4.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_5.png");
	pJuniorKnight->SetParticleTextureNames(vTextureNames);

	shared_ptr<Selector> pParentSelector = make_shared<Selector>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pWalkSequence = make_shared<Sequence>();

	pParentSelector->AddChild(pDeadSequence);
	pParentSelector->AddChild(pHitSequence);
	pParentSelector->AddChild(pAttackSequence);
	pParentSelector->AddChild(pWalkSequence);

	shared_ptr<MoveTask> pMoveTask = make_shared<MoveTask>(pJuniorKnight);
	shared_ptr<IsPlayerNearCondition> pNearCondition = make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pJuniorKnight);
	shared_ptr<RunAnimateTask> pRunWalkAnimation = make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Walk");
	shared_ptr<RunAnimateTask> pRunAttackAnimation = make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Attack");
	shared_ptr<RunAnimateTask> pRunIdleAnimation = make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Idle");
	shared_ptr<RunAnimateTask> pRunHitAnimation = make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Weak_Hit");
	shared_ptr<DelayTask> pDelayTask = make_shared<DelayTask>(pJuniorKnight, 1.f);
	shared_ptr<IsHitCondition> pHitCondition = make_shared<IsHitCondition>(pJuniorKnight);

	shared_ptr<IsDeadCondition> pDeadCondition = make_shared<IsDeadCondition>(pJuniorKnight);
	shared_ptr<RemoveObjectTask> pRemoveTask = make_shared<RemoveObjectTask>(pJuniorKnight);
	shared_ptr<IsPlayerInAttackRangeCondition> pPlayerInAttackRangeCondition = make_shared<IsPlayerInAttackRangeCondition>(m_pPlayer.lock(), pJuniorKnight);
	shared_ptr<PlayerHitTask> pPlayerHitTask = make_shared<PlayerHitTask>(m_pPlayer.lock(), pJuniorKnight);

	pDeadSequence->AddChild(pDeadCondition);
	pDeadSequence->AddChild(pRemoveTask);

	pHitSequence->AddChild(pHitCondition);
	pHitSequence->AddChild(pRunHitAnimation);
	pHitSequence->AddChild(pDelayTask);

	pAttackSequence->AddChild(pNearCondition);
	pAttackSequence->AddChild(pRunAttackAnimation);
	pAttackSequence->AddChild(pPlayerInAttackRangeCondition);
	pAttackSequence->AddChild(pPlayerHitTask);

	pWalkSequence->AddChild(pRunWalkAnimation);
	pWalkSequence->AddChild(pMoveTask);

	pJuniorKnight->GetAI()->SetBehaviorRootNode(pParentSelector);

	shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"JuniorKnight_Idle", L"..\\Resources\\Animation\\JuniorKnight\\junior_knight_idle.anim");
	shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->LoadAnimation(L"JuniorKnight_Walk", L"..\\Resources\\Animation\\JuniorKnight\\junior_knight_walk.anim");
	shared_ptr<Animation> pAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"JuniorKnight_Attack", L"..\\Resources\\Animation\\JuniorKnight\\junior_knight_attack.anim");
	shared_ptr<Animation> pWeakHitAnimation = GET_SINGLE(Resources)->LoadAnimation(L"JuniorKnight_Weak_Hit", L"..\\Resources\\Animation\\JuniorKnight\\junior_knight_weak_hit.anim");
	pJuniorKnight->GetAnimator()->AddAnimation(L"JuniorKnight_Idle", pIdleAnimation);
	pJuniorKnight->GetAnimator()->AddAnimation(L"JuniorKnight_Walk", pWalkAnimation);
	pJuniorKnight->GetAnimator()->AddAnimation(L"JuniorKnight_Attack", pAttackAnimation);
	pJuniorKnight->GetAnimator()->AddAnimation(L"JuniorKnight_Weak_Hit", pWeakHitAnimation);
	pJuniorKnight->GetAnimator()->Play(L"JuniorKnight_Idle");

	pAttackAnimation->SetHitFrame(1);

	pJuniorKnight->GetTransform()->SetLocalPosition(vMonsterPos);
	return pJuniorKnight;
}

void ObjectFactory::CreateSpawnEffectAndAddedScene(const Vec3& vMonsterPos)
{
	shared_ptr<AnimationLocalEffect> pSpawnEffect = CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pSpawnEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pSpawnAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Monster_Spawn", L"..\\Resources\\Animation\\MonsterCommon\\monster_spawn.anim");
	pSpawnEffect->GetAnimator()->AddAnimation(L"Monster_Spawn", pSpawnAnimation);
	pSpawnEffect->GetAnimator()->Play(L"Monster_Spawn", false);

	pSpawnEffect->GetTransform()->SetLocalPosition(vMonsterPos);
	pSpawnEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSpawnEffect, eSceneType));
}

shared_ptr<Item> ObjectFactory::CreateForbiddenSword()
{
	ItemInfo itemInfo = {};
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"ForbiddenSword_Vignette", L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"ForbiddenSword", L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword.png");
	
	itemInfo.eGrade = GRADE::UNIQUE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();
	
	itemInfo.szName = L"���ε� ��";
	itemInfo.szComment = L"������ ������ �����Ǿ� �ִ� ��. �̼��� ������ ��������.";
	itemInfo.szExplanation = L"�������ݷ��� 15% �����մϴ�.\n300���� �� óġ �� �� �������� '����: Ű����'���� ���մϴ�";

	shared_ptr<Item> pForbiddenSword = make_shared<ForbiddenSword>(itemInfo);

	return pForbiddenSword;
}

shared_ptr<Item> ObjectFactory::CreateEvilSwordKirion()
{
	ItemInfo itemInfo = {};
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"EvilSwordKirion_Vignette", L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"EvilSwordKirion", L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion.png");
	
	itemInfo.eGrade = GRADE::REGENDARY;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"����: Ű����";
	itemInfo.szComment = L"������� ����ϴ� ���ֹ��� ����, �ǰ� �帣�� �̴� ����� ���� �� ����.";
	itemInfo.szExplanation = L"�������ݷ��� 60% �����մϴ�.\n�⺻���� �� �뽬 �� ������ �߻��Ͽ� ������������ �����ϴ�.";

	shared_ptr<Item> pDemonSwordKirion = make_shared<EvilSwordKirion>(itemInfo);

	return pDemonSwordKirion;
}

shared_ptr<Essence> ObjectFactory::CreateLyweasel()
{
	EssenceInfo essenceInfo = {};
	essenceInfo.szName = L"��������";
	essenceInfo.szSkillName = L"����";
	essenceInfo.szComment = L"�ʹ� ���� ���� �� �� ������ ��ü�� �� �� ������ ���� ����";
	essenceInfo.szExplanation = L"���������� ��Ÿ�� ������ ������ ������������ �����ϴ�.\n�뽬�Ÿ��� 30%�����ϰ� �뽬�Ÿ��� ������ ������ ������������ �����ϴ�";
	essenceInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"Lyweasel_Vignette", L"..\\Resources\\Texture\\Essence\\Lyweasel\\Lyweasel_Vignette.png");
	essenceInfo.pEssenceTexture = GET_SINGLE(Resources)->Load<Texture>(L"Lyweasel", L"..\\Resources\\Texture\\Essence\\Lyweasel\\Lyweasel.png");
	essenceInfo.eGrade = GRADE::RARE;

	essenceInfo.fCooldown = 5.f;
	essenceInfo.fDuration = 1.f;
	essenceInfo.eEssenceType = ESSENCE_TYPE::CONTINUOUS;

	shared_ptr<Essence> pLyweasel = make_shared<Lyweasel>(essenceInfo);
	return pLyweasel;
}

shared_ptr<Essence> ObjectFactory::CreateWisp()
{
	return shared_ptr<Essence>();
}
