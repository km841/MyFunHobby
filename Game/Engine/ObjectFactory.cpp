#include "pch.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"
#include "ErodedKnight.h"
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
#include "PatrolTask.h"
#include "RunAnimateTask.h"
#include "Selector.h"
#include "DelayTask.h"
#include "IsHitCondition.h"
#include "IsDeadCondition.h"
#include "RemoveObjectTask.h"
#include "IsPlayerInAttackRangeCondition.h"
#include "PlayerHitTask.h"
#include "TimerCondition.h"
#include "IsMonsterStateCondition.h"
#include "ChangeMonsterStateTask.h"
#include "TrackingOfMeleeTask.h"
#include "KnightAttackTask.h"
#include "UnflagAsAttackedFlagTask.h"
#include "DeadEventTriggerTask.h"

/* Engrave */
#include "Rapidity.h"
#include "Arms.h"

/* Script */
#include "ErodedKnightDeadScript.h"

void ObjectFactory::CreateMonsterAndAddedScene(MONSTER_KIND eMonsterKind, const Vec3& vMonsterPos)
{
	shared_ptr<Monster> pMonster = nullptr;

	switch (eMonsterKind)
	{
	case MONSTER_KIND::JUNIOR_KNIGHT:
		pMonster = CreateJuniorKnight(vMonsterPos);
		break;

	case MONSTER_KIND::ERODED_KNIGHT:
		pMonster = CreateErodedKnight(vMonsterPos);
		break;
	}

	assert(pMonster);

	pMonster->Awake();
	pMonster->Start();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMonster, eSceneType));

	CreateSpawnEffectAndAddedScene(vMonsterPos);
}

shared_ptr<Monster> ObjectFactory::CreateJuniorKnight(const Vec3& vMonsterPos)
{
	shared_ptr<JuniorKnight> pJuniorKnight = CreateObjectHasPhysicalFromPool<JuniorKnight>(L"Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
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

	shared_ptr<Selector> pRootNode = make_shared<Selector>();
	shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPatrolSequence = make_shared<Sequence>();
	shared_ptr<Selector> pPatrolSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pPlayerEncounterSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTraceSequence = make_shared<Sequence>();
	shared_ptr<Selector> pTraceSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();	
	shared_ptr<Sequence> pWeakHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();

	pRootNode->AddChild(pDeadSequence);
	pDeadSequence->AddChild(make_shared<IsDeadCondition>(pJuniorKnight));
	pDeadSequence->AddChild(make_shared<RemoveObjectTask>(pJuniorKnight));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<TimerCondition>(pJuniorKnight, 0.5f));
	pWeakHitSequence->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::TRACE));

	pRootNode->AddChild(pIdleSequence);
	pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::IDLE));
	pIdleSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Idle"));
	pIdleSequence->AddChild(make_shared<TimerCondition>(pJuniorKnight, 1.f));
	pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::PATROL));

	pRootNode->AddChild(pPatrolSequence);
	pPatrolSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::PATROL));
	pPatrolSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Walk"));
	pPatrolSequence->AddChild(pPatrolSubSelector);
	pPatrolSequence->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::IDLE));

	pPatrolSubSelector->AddChild(make_shared<PatrolTask>(pJuniorKnight, 50.f, 200.f));
	pPatrolSubSelector->AddChild(pPlayerEncounterSequence);

	pPlayerEncounterSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pJuniorKnight));
	pPlayerEncounterSequence->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::TRACE));

	pRootNode->AddChild(pTraceSequence);
	pTraceSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::TRACE));
	pTraceSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Walk"));
	pTraceSequence->AddChild(pTraceSubSelector);

	pTraceSubSelector->AddChild(make_shared<TrackingOfMeleeTask>(m_pPlayer.lock(), pJuniorKnight));
	pTraceSubSelector->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::ATTACK));

	pRootNode->AddChild(pAttackSequence);
	pAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::ATTACK));
	pAttackSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Attack", false));
	pAttackSequence->AddChild(make_shared<KnightAttackTask>(m_pPlayer.lock(), pJuniorKnight));
	pAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pJuniorKnight, MONSTER_STATE::IDLE));
	
	pJuniorKnight->GetAI()->SetBehaviorRootNode(pRootNode);

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

	pJuniorKnight->UnflagAsAttacked();

	pJuniorKnight->GetTransform()->SetLocalPosition(vMonsterPos);
	return pJuniorKnight;
}

shared_ptr<Monster> ObjectFactory::CreateErodedKnight(const Vec3& vMonsterPos)
{
	shared_ptr<ErodedKnight> pErodedKnight = CreateObjectHasPhysicalFromPool<ErodedKnight>(L"Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
	pErodedKnight->AddComponent(make_shared<AI>());
	pErodedKnight->AddComponent(make_shared<Animator>());
	pErodedKnight->AddComponent(make_shared<Movement>());
	pErodedKnight->AddComponent(make_shared<ErodedKnightDeadScript>());

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\JuniorKnight\\";
	std::vector<wstring> vTextureNames;
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_1.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_2.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_3.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_4.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_5.png");

	pErodedKnight->SetParticleTextureNames(vTextureNames);

	shared_ptr<Selector> pRootNode = make_shared<Selector>();
	shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPatrolSequence = make_shared<Sequence>();
	shared_ptr<Selector> pPatrolSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pPlayerEncounterSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTraceSequence = make_shared<Sequence>();
	shared_ptr<Selector> pTraceSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pWeakHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();

	pRootNode->AddChild(pDeadSequence);
	pDeadSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::DEAD));
	pDeadSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Dead"));
	pDeadSequence->AddChild(make_shared<DeadEventTriggerTask>(pErodedKnight));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<TimerCondition>(pErodedKnight, 0.5f));
	pWeakHitSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::TRACE));

	pRootNode->AddChild(pIdleSequence);
	pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::IDLE));
	pIdleSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Idle"));
	pIdleSequence->AddChild(make_shared<TimerCondition>(pErodedKnight, 1.f));
	pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::PATROL));

	pRootNode->AddChild(pPatrolSequence);
	pPatrolSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::PATROL));
	pPatrolSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Walk"));
	pPatrolSequence->AddChild(pPatrolSubSelector);
	pPatrolSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::IDLE));

	pPatrolSubSelector->AddChild(make_shared<PatrolTask>(pErodedKnight, 50.f, 200.f));
	pPatrolSubSelector->AddChild(pPlayerEncounterSequence);

	pPlayerEncounterSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pErodedKnight));
	pPlayerEncounterSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::TRACE));

	pRootNode->AddChild(pTraceSequence);
	pTraceSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::TRACE));
	pTraceSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Walk"));
	pTraceSequence->AddChild(pTraceSubSelector);

	pTraceSubSelector->AddChild(make_shared<TrackingOfMeleeTask>(m_pPlayer.lock(), pErodedKnight));
	pTraceSubSelector->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::ATTACK));

	pRootNode->AddChild(pAttackSequence);
	pAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::ATTACK));
	pAttackSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Attack", false));
	pAttackSequence->AddChild(make_shared<KnightAttackTask>(m_pPlayer.lock(), pErodedKnight));
	pAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedKnight, MONSTER_STATE::IDLE));

	pErodedKnight->GetAI()->SetBehaviorRootNode(pRootNode);

	shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedKnight_Idle", L"..\\Resources\\Animation\\ErodedKnight\\Eroded_knight_idle.anim");
	shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedKnight_Walk", L"..\\Resources\\Animation\\ErodedKnight\\Eroded_knight_walk.anim");
	shared_ptr<Animation> pAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedKnight_Attack", L"..\\Resources\\Animation\\ErodedKnight\\Eroded_knight_attack.anim");
	shared_ptr<Animation> pWeakHitAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedKnight_Weak_Hit", L"..\\Resources\\Animation\\ErodedKnight\\Eroded_knight_weak_hit.anim");
	shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedKnight_Dead", L"..\\Resources\\Animation\\ErodedKnight\\Eroded_knight_dead.anim");
	pErodedKnight->GetAnimator()->AddAnimation(L"ErodedKnight_Idle", pIdleAnimation);
	pErodedKnight->GetAnimator()->AddAnimation(L"ErodedKnight_Walk", pWalkAnimation);
	pErodedKnight->GetAnimator()->AddAnimation(L"ErodedKnight_Attack", pAttackAnimation);
	pErodedKnight->GetAnimator()->AddAnimation(L"ErodedKnight_Weak_Hit", pWeakHitAnimation);
	pErodedKnight->GetAnimator()->AddAnimation(L"ErodedKnight_Dead", pDeadAnimation);
	pErodedKnight->GetAnimator()->Play(L"ErodedKnight_Idle");

	pAttackAnimation->SetHitFrame(1);

	pErodedKnight->UnflagAsAttacked();

	pErodedKnight->GetTransform()->SetLocalPosition(vMonsterPos);
	return pErodedKnight;
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
	
	itemInfo.eGrade = GRADE::LEGENDARY;
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
