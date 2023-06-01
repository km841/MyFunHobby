#include "pch.h"
#include "ObjectFactory.h"
#include "JuniorKnight.h"
#include "ErodedKnight.h"
#include "ErodedEnt.h"
#include "Alchemist.h"
#include "ErodedHeavyInfantry.h"
#include "PlayerChangeStateEvent.h"
#include "Sequence.h"
#include "Selector.h"
#include "AI.h"
#include "Animator.h"
#include "Animation.h"
#include "AnimationLocalEffect.h"
#include "JennysChainSickle.h"
#include "InvisibleKnife.h"
#include "RingOfMoon.h"
#include "SwordOfSun.h"
#include "BoneOfMana.h"
#include "GunpowderSword.h"
#include "ThiefsBlackIronDaggers.h"
#include "RavenLordsFeather.h"
#include "VoodooDoll.h"
#include "BrightDawn.h"

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
#include "InfantryTackleTask.h"
#include "SetDirectionTowardPlayerTask.h"
#include "IsFinishedRageAttackCondition.h"
#include "IncreaseAttackCountTask.h"
#include "RandomDirectionTask.h"
#include "VelocityDownTask.h"

/* Engrave */
#include "Rapidity.h"
#include "Arms.h"

/* Script */
#include "ErodedKnightDeadScript.h"
#include "ErodedHeavyInfantryTackleScript.h"
#include "ErodedHeavyInfantryAttackScript.h"
#include "ErodedHeavyInfantryDeadScript.h"
#include "ErodedEntSkillScript.h"
#include "AlchemistFlaskThrowScript.h"
#include "ErodedEntDeadScript.h"
#include "ErodedEntAttackScript.h"
#include "MonsterHitShaderScript.h"


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

	case MONSTER_KIND::ERODED_HEAVY_INFANTRY:
		pMonster = CreateErodedHeavyInfantry(vMonsterPos);
		break;

	case MONSTER_KIND::ERODED_ENT:
		pMonster = CreateErodedEnt(vMonsterPos);
		break;

	case MONSTER_KIND::ALCHEMIST:
		pMonster = CreateAlchemist(vMonsterPos);
		break;
	}

	assert(pMonster);
	pMonster->AddComponent(make_shared<MonsterHitShaderScript>());

	pMonster->Awake();
	pMonster->Start();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMonster, eSceneType));

	CreateSpawnEffectAndAddedScene(vMonsterPos);
}

shared_ptr<Monster> ObjectFactory::CreateJuniorKnight(const Vec3& vMonsterPos)
{
	shared_ptr<JuniorKnight> pJuniorKnight = CreateObjectHasPhysicalFromPool<JuniorKnight>(L"Monster_Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
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
	pDeadSequence->AddChild(make_shared<DeadEventTriggerTask>(pJuniorKnight));
	pDeadSequence->AddChild(make_shared<RemoveObjectTask>(pJuniorKnight));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pJuniorKnight, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pJuniorKnight, L"JuniorKnight_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<VelocityDownTask>(pJuniorKnight));
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

	pAttackAnimation->SetHitFrame(2);

	pJuniorKnight->UnflagAsAttacked();

	pJuniorKnight->GetTransform()->SetLocalPosition(vMonsterPos);
	return pJuniorKnight;
}

shared_ptr<Monster> ObjectFactory::CreateErodedKnight(const Vec3& vMonsterPos)
{
	shared_ptr<ErodedKnight> pErodedKnight = CreateObjectHasPhysicalFromPool<ErodedKnight>(L"Monster_Deferred", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
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
	pDeadSequence->AddChild(make_shared<VelocityDownTask>(pErodedKnight));
	pDeadSequence->AddChild(make_shared<DeadEventTriggerTask>(pErodedKnight));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedKnight, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pErodedKnight, L"ErodedKnight_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<VelocityDownTask>(pErodedKnight));
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

shared_ptr<Monster> ObjectFactory::CreateErodedHeavyInfantry(const Vec3& vMonsterPos)
{
	shared_ptr<ErodedHeavyInfantry> pErodedHeavyInfantry = CreateObjectHasPhysicalFromPool<ErodedHeavyInfantry>(L"Monster_Deferred", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(100.f, 100.f, 50.f), MassProperties(10.f, 10.f, 0.01f));
	pErodedHeavyInfantry->AddComponent(make_shared<AI>());
	pErodedHeavyInfantry->AddComponent(make_shared<Animator>());
	pErodedHeavyInfantry->AddComponent(make_shared<Movement>());
	pErodedHeavyInfantry->AddComponent(make_shared<ErodedHeavyInfantryDeadScript>());
	pErodedHeavyInfantry->AddComponent(make_shared<ErodedHeavyInfantryTackleScript>());
	pErodedHeavyInfantry->AddComponent(make_shared<ErodedHeavyInfantryAttackScript>());

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\JuniorKnight\\";
	std::vector<wstring> vTextureNames;
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_1.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_2.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_3.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_4.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_5.png");

	pErodedHeavyInfantry->SetParticleTextureNames(vTextureNames);

	shared_ptr<Selector> pRootNode = make_shared<Selector>();
	shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPatrolSequence = make_shared<Sequence>();
	shared_ptr<Selector> pPatrolSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pPlayerEncounterAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPlayerEncounterTackleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTraceSequence = make_shared<Sequence>();
	shared_ptr<Selector> pTraceSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pWeakHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();

	shared_ptr<Sequence> pAttackReadySequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackStartSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackLoopSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackEndSequence = make_shared<Sequence>();

	shared_ptr<Sequence> pTackleReadySequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTackleLoopSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTackleEndSequence = make_shared<Sequence>();

	shared_ptr<Sequence> pRageAttackReadySequence = make_shared<Sequence>();
	shared_ptr<Sequence> pRageAttackStartSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pRageAttackSequence = make_shared<Sequence>();

	shared_ptr<Sequence> pRageTackleReadySequence = make_shared<Sequence>();
	shared_ptr<Sequence> pRageTackleLoopSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pRageTackleEndSequence = make_shared<Sequence>();

	shared_ptr<Sequence> pRageAttackSubSequence = make_shared<Sequence>();
	shared_ptr<Selector> pRageAttackReturnSelector = make_shared<Selector>();
	shared_ptr<Sequence> pIncreaseAttackCountSequence = make_shared<Sequence>();

	pRootNode->AddChild(pDeadSequence);
	pDeadSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::DEAD));
	pDeadSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Dead"));
	pDeadSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 3.f));
	pDeadSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_ATTACK_START));
	
	pRootNode->AddChild(pRageAttackStartSequence);
	pRageAttackStartSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_ATTACK_START));
	pRageAttackStartSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"Rage_ErodedHeavyInfantry_Attack_Start", false));
	pRageAttackStartSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 0.1f));
	pRageAttackStartSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_ATTACK));

	pRootNode->AddChild(pRageAttackSequence);
	pRageAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_ATTACK));
	pRageAttackSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"Rage_ErodedHeavyInfantry_Attack", false));
	pRageAttackSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 0.3f));
	pRageAttackSequence->AddChild(pRageAttackReturnSelector);

	pRageAttackReturnSelector->AddChild(pRageAttackSubSequence);
	pRageAttackReturnSelector->AddChild(pIncreaseAttackCountSequence);

	pIncreaseAttackCountSequence->AddChild(make_shared<IncreaseAttackCountTask>(pErodedHeavyInfantry));
	pIncreaseAttackCountSequence->AddChild(make_shared<RandomDirectionTask>(pErodedHeavyInfantry));
	pIncreaseAttackCountSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_ATTACK_START, true));

	pRageAttackSubSequence->AddChild(make_shared<IsFinishedRageAttackCondition>(pErodedHeavyInfantry, 4));
	pRageAttackSubSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_TACKLE_READY, true));

	pRootNode->AddChild(pRageTackleReadySequence);
	pRageTackleReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_TACKLE_READY));
	pRageTackleReadySequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"Rage_ErodedHeavyInfantry_Tackle_Ready", false));
	pRageTackleReadySequence->AddChild(make_shared<DeadEventTriggerTask>(pErodedHeavyInfantry));
	pRageTackleReadySequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pErodedHeavyInfantry));
	pRageTackleReadySequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 0.8f));
	pRageTackleReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_TACKLE_LOOP));

	pRootNode->AddChild(pRageTackleLoopSequence);
	pRageTackleLoopSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_TACKLE_LOOP));
	pRageTackleLoopSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"Rage_ErodedHeavyInfantry_Tackle_Loop", false));
	pRageTackleLoopSequence->AddChild(make_shared<InfantryTackleTask>(m_pPlayer.lock(), pErodedHeavyInfantry));
	pRageTackleLoopSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::RAGE_TACKLE_END));

	pRootNode->AddChild(pIdleSequence);
	pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::IDLE));
	pIdleSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Idle"));
	pIdleSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 1.f));
	pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::PATROL));

	pRootNode->AddChild(pPatrolSequence);
	pPatrolSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::PATROL));
	pPatrolSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Walk"));
	pPatrolSequence->AddChild(pPatrolSubSelector);
	pPatrolSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::IDLE));

	pPatrolSubSelector->AddChild(make_shared<PatrolTask>(pErodedHeavyInfantry, 50.f, 200.f));

	pPatrolSubSelector->AddChild(pPlayerEncounterTackleSequence);
	pPlayerEncounterTackleSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pErodedHeavyInfantry, 500.f));
	pPlayerEncounterTackleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::TACKLE_READY));

	pPatrolSubSelector->AddChild(pPlayerEncounterAttackSequence);
	pPlayerEncounterAttackSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pErodedHeavyInfantry, 300.f));
	pPlayerEncounterAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_READY));

	pRootNode->AddChild(pAttackReadySequence);
	pAttackReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_READY));
	pAttackReadySequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Attack_Ready", false));
	pAttackReadySequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pErodedHeavyInfantry));
	pAttackReadySequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 0.8f));
	pAttackReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_START));

	pRootNode->AddChild(pAttackStartSequence);
	pAttackStartSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_START));
	pAttackStartSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Attack_Start", false));
	pAttackStartSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 0.2f));
	pAttackStartSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK));

	pRootNode->AddChild(pAttackSequence);
	pAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK));
	pAttackSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Attack", false));
	pAttackSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 1.2f));
	pAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_END));

	pRootNode->AddChild(pAttackEndSequence);
	pAttackEndSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::ATTACK_END));
	pAttackEndSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Attack_End", false));
	pAttackEndSequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 1.f));
	pAttackEndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::IDLE));

	pRootNode->AddChild(pTackleReadySequence);
	pTackleReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::TACKLE_READY));
	pTackleReadySequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Tackle_Ready"));
	pTackleReadySequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pErodedHeavyInfantry));
	pTackleReadySequence->AddChild(make_shared<TimerCondition>(pErodedHeavyInfantry, 1.f));
	pTackleReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::TACKLE_LOOP));

	pRootNode->AddChild(pTackleLoopSequence);
	pTackleLoopSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedHeavyInfantry, MONSTER_STATE::TACKLE_LOOP));
	pTackleLoopSequence->AddChild(make_shared<RunAnimateTask>(pErodedHeavyInfantry, L"ErodedHeavyInfantry_Tackle_Loop"));
	pTackleLoopSequence->AddChild(make_shared<InfantryTackleTask>(m_pPlayer.lock(), pErodedHeavyInfantry));
	pTackleLoopSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedHeavyInfantry, MONSTER_STATE::IDLE));

	pErodedHeavyInfantry->GetAI()->SetBehaviorRootNode(pRootNode);

	shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Idle", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_idle.anim");
	shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Walk", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_walk.anim");
	shared_ptr<Animation> pAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Attack", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_attack.anim");
	shared_ptr<Animation> pAttackReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Attack_Ready", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_attack_ready.anim");
	shared_ptr<Animation> pAttackStartAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Attack_Start", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_attack_start.anim");
	shared_ptr<Animation> pAttackLoopAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Attack_Loop", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_attack_loop.anim");
	shared_ptr<Animation> pAttackEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Attack_End", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_attack_end.anim");
	shared_ptr<Animation> pTackleReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Tackle_Ready", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_tackle_ready.anim");
	shared_ptr<Animation> pTackleLoopAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Tackle_Loop", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_tackle_loop.anim");
	shared_ptr<Animation> pTackleEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Tackle_End", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_tackle_end.anim");
	shared_ptr<Animation> pDeadReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Dead_Ready", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_dead_ready.anim");
	shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Dead", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_dead.anim");

	shared_ptr<Animation> pRageAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Attack", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_attack.anim");
	shared_ptr<Animation> pRageAttackReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Attack_Ready", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_attack_ready.anim");
	shared_ptr<Animation> pRageAttackStartAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Attack_Start", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_attack_start.anim");
	shared_ptr<Animation> pRageAttackLoopAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Attack_Loop", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_attack_loop.anim");
	shared_ptr<Animation> pRageAttackEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Attack_End", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_attack_end.anim");
	shared_ptr<Animation> pRageTackleReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Tackle_Ready", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_tackle_ready.anim");
	shared_ptr<Animation> pRageTackleLoopAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Tackle_Loop", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_tackle_loop.anim");
	shared_ptr<Animation> pRageTackleEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rage_ErodedHeavyInfantry_Tackle_End", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\m2_eroded_heavy_infantry_tackle_end.anim");
	
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Idle", pIdleAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Walk", pWalkAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Attack", pAttackAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Attack_Ready", pAttackReadyAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Attack_Start", pAttackStartAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Attack_Loop", pAttackLoopAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Attack_End", pAttackEndAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Tackle_Ready", pTackleReadyAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Tackle_Loop", pTackleLoopAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Tackle_End", pTackleEndAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Dead_Ready", pDeadReadyAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Dead", pDeadAnimation);

	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Attack", pRageAttackAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Attack_Ready", pRageAttackReadyAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Attack_Start", pRageAttackStartAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Attack_Loop", pRageAttackLoopAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Attack_End", pRageAttackEndAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Tackle_Ready", pRageTackleReadyAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Tackle_Loop", pRageTackleLoopAnimation);
	pErodedHeavyInfantry->GetAnimator()->AddAnimation(L"Rage_ErodedHeavyInfantry_Tackle_End", pRageTackleEndAnimation);

	pAttackAnimation->SetHitFrame(1);
	pRageAttackAnimation->SetHitFrame(1);

	pErodedHeavyInfantry->GetAnimator()->Play(L"ErodedHeavyInfantry_Idle");
	pErodedHeavyInfantry->UnflagAsAttacked();

	pErodedHeavyInfantry->GetTransform()->SetLocalPosition(vMonsterPos);
	return pErodedHeavyInfantry;
}

shared_ptr<Monster> ObjectFactory::CreateErodedEnt(const Vec3& vMonsterPos)
{
	shared_ptr<ErodedEnt> pErodedEnt = CreateObjectHasPhysicalFromPool<ErodedEnt>(L"Monster_Deferred", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
	pErodedEnt->AddComponent(make_shared<AI>());
	pErodedEnt->AddComponent(make_shared<Animator>());
	pErodedEnt->AddComponent(make_shared<Movement>());
	pErodedEnt->AddComponent(make_shared<ErodedEntDeadScript>());
	pErodedEnt->AddComponent(make_shared<ErodedEntSkillScript>());
	pErodedEnt->AddComponent(make_shared<ErodedEntAttackScript>());

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\JuniorKnight\\";
	std::vector<wstring> vTextureNames;
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_1.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_2.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_3.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_4.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_5.png");

	pErodedEnt->SetParticleTextureNames(vTextureNames);

	shared_ptr<Selector> pRootNode = make_shared<Selector>();
	shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPatrolSequence = make_shared<Sequence>();
	shared_ptr<Selector> pPatrolSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pHeadingToSkillSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pHeadingToAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pAttackReturnSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pSkillReadySequence = make_shared<Sequence>();
	shared_ptr<Sequence> pSkillSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pSkillEndSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pWeakHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();

	pRootNode->AddChild(pDeadSequence);
	pDeadSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::DEAD));
	pDeadSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Dead"));
	pDeadSequence->AddChild(make_shared<DeadEventTriggerTask>(pErodedEnt));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 0.5f));
	pWeakHitSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::IDLE));

	pRootNode->AddChild(pIdleSequence);
	pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::IDLE));
	pIdleSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Idle"));
	pIdleSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 1.f));
	pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::PATROL));

	pRootNode->AddChild(pPatrolSequence);
	pPatrolSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::PATROL));
	pPatrolSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Walk"));
	pPatrolSequence->AddChild(pPatrolSubSelector);
	pPatrolSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::IDLE));

	pPatrolSubSelector->AddChild(make_shared<PatrolTask>(pErodedEnt, 50.f, 200.f));
	pPatrolSubSelector->AddChild(pHeadingToSkillSequence);
	pPatrolSubSelector->AddChild(pHeadingToAttackSequence);

	pHeadingToSkillSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pErodedEnt, 500.f));
	pHeadingToSkillSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::SKILL1_READY));

	pHeadingToAttackSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pErodedEnt, 300.f));
	pHeadingToAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::ATTACK));

	pRootNode->AddChild(pAttackSequence);
	pAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::ATTACK));
	pAttackSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Attack", false));
	pAttackSequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pErodedEnt));
	pAttackSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 1.3f));
	pAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::ATTACK_END));

	pRootNode->AddChild(pAttackReturnSequence);
	pAttackReturnSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::ATTACK_END));
	pAttackReturnSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Attack_Return", false));
	pAttackReturnSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 0.3f));
	pAttackReturnSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::IDLE));

	pRootNode->AddChild(pSkillReadySequence);
	pSkillReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::SKILL1_READY));
	pSkillReadySequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Idle", false));
	pSkillReadySequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pErodedEnt));
	pSkillReadySequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 0.5f));
	pSkillReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::SKILL1));

	pRootNode->AddChild(pSkillSequence);
	pSkillSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::SKILL1));
	pSkillSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Skill", false));
	pSkillSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 1.3f));
	pSkillSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::SKILL1_END));

	pRootNode->AddChild(pSkillEndSequence);
	pSkillEndSequence->AddChild(make_shared<IsMonsterStateCondition>(pErodedEnt, MONSTER_STATE::SKILL1_END));
	pSkillEndSequence->AddChild(make_shared<RunAnimateTask>(pErodedEnt, L"ErodedEnt_Skill_End", false));
	pSkillEndSequence->AddChild(make_shared<TimerCondition>(pErodedEnt, 0.8f));
	pSkillEndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pErodedEnt, MONSTER_STATE::IDLE));

	pErodedEnt->GetAI()->SetBehaviorRootNode(pRootNode);

	shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Idle", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_idle.anim");
	shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Walk", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_walk.anim");
	shared_ptr<Animation> pAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Attack", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_thorn.anim");
	shared_ptr<Animation> pAttackReturnAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Attack_Return", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_thorn_return.anim");
	shared_ptr<Animation> pSkillAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Skill", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_skill.anim");
	shared_ptr<Animation> pSkillEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Skill_End", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_skill_end.anim");
	shared_ptr<Animation> pWeakHitAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Weak_Hit", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_weak_hit.anim");
	shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedEnt_Dead", L"..\\Resources\\Animation\\ErodedEnt\\eroded_ent_dead.anim");
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Idle", pIdleAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Walk", pWalkAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Attack", pAttackAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Attack_Return", pAttackReturnAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Skill", pSkillAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Skill_End", pSkillEndAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Weak_Hit", pWeakHitAnimation);
	pErodedEnt->GetAnimator()->AddAnimation(L"ErodedEnt_Dead", pDeadAnimation);
	pErodedEnt->GetAnimator()->Play(L"ErodedEnt_Idle");

	pAttackAnimation->SetHitFrame(6);

	pErodedEnt->UnflagAsAttacked();

	pErodedEnt->GetTransform()->SetLocalPosition(vMonsterPos);
	return pErodedEnt;
}

shared_ptr<Monster> ObjectFactory::CreateAlchemist(const Vec3 vMonsterPos)
{
	shared_ptr<Alchemist> pAlchemist = CreateObjectHasPhysicalFromPool<Alchemist>(L"Monster_Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
	pAlchemist->AddComponent(make_shared<AI>());
	pAlchemist->AddComponent(make_shared<Animator>());
	pAlchemist->AddComponent(make_shared<Movement>());
	pAlchemist->AddComponent(make_shared<AlchemistFlaskThrowScript>());

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\JuniorKnight\\";
	std::vector<wstring> vTextureNames;
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_1.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_2.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_3.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_4.png");
	vTextureNames.push_back(szResourcePath + L"Image_Junior_Knight_Particle_5.png");
	pAlchemist->SetParticleTextureNames(vTextureNames);

	shared_ptr<Selector> pRootNode = make_shared<Selector>();
	shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pPatrolSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pHeadingToAttackSequence = make_shared<Sequence>();
	shared_ptr<Selector> pPatrolSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pPlayerEncounterSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pTraceSequence = make_shared<Sequence>();
	shared_ptr<Selector> pTraceSubSelector = make_shared<Selector>();
	shared_ptr<Sequence> pAttackSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pWeakHitSequence = make_shared<Sequence>();
	shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();

	pRootNode->AddChild(pDeadSequence);
	pDeadSequence->AddChild(make_shared<IsDeadCondition>(pAlchemist));
	pDeadSequence->AddChild(make_shared<DeadEventTriggerTask>(pAlchemist));
	pDeadSequence->AddChild(make_shared<RemoveObjectTask>(pAlchemist));

	pRootNode->AddChild(pWeakHitSequence);
	pWeakHitSequence->AddChild(make_shared<IsMonsterStateCondition>(pAlchemist, MONSTER_STATE::WEAK_HIT));
	pWeakHitSequence->AddChild(make_shared<RunAnimateTask>(pAlchemist, L"Alchemist_Weak_Hit"));
	pWeakHitSequence->AddChild(make_shared<TimerCondition>(pAlchemist, 0.5f));
	pWeakHitSequence->AddChild(make_shared<ChangeMonsterStateTask>(pAlchemist, MONSTER_STATE::IDLE));

	pRootNode->AddChild(pIdleSequence);
	pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pAlchemist, MONSTER_STATE::IDLE));
	pIdleSequence->AddChild(make_shared<RunAnimateTask>(pAlchemist, L"Alchemist_Idle"));
	pIdleSequence->AddChild(make_shared<TimerCondition>(pAlchemist, 1.f));
	pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pAlchemist, MONSTER_STATE::PATROL));

	pRootNode->AddChild(pPatrolSequence);
	pPatrolSequence->AddChild(make_shared<IsMonsterStateCondition>(pAlchemist, MONSTER_STATE::PATROL));
	pPatrolSequence->AddChild(make_shared<RunAnimateTask>(pAlchemist, L"Alchemist_Walk"));
	pPatrolSequence->AddChild(pPatrolSubSelector);
	
	pPatrolSubSelector->AddChild(make_shared<PatrolTask>(pAlchemist, 50.f, 200.f));
	pPatrolSubSelector->AddChild(pHeadingToAttackSequence);

	pHeadingToAttackSequence->AddChild(make_shared<IsPlayerNearCondition>(m_pPlayer.lock(), pAlchemist, 500.f));
	pHeadingToAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pAlchemist, MONSTER_STATE::ATTACK, false));

	pRootNode->AddChild(pAttackSequence);
	pAttackSequence->AddChild(make_shared<IsMonsterStateCondition>(pAlchemist, MONSTER_STATE::ATTACK));
	pAttackSequence->AddChild(make_shared<RunAnimateTask>(pAlchemist, L"Alchemist_Attack", false));
	pAttackSequence->AddChild(make_shared<SetDirectionTowardPlayerTask>(m_pPlayer.lock(), pAlchemist));
	pAttackSequence->AddChild(make_shared<TimerCondition>(pAlchemist, 1.5f));
	pAttackSequence->AddChild(make_shared<ChangeMonsterStateTask>(pAlchemist, MONSTER_STATE::IDLE));

	pAlchemist->GetAI()->SetBehaviorRootNode(pRootNode);

	shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Alchemist_Idle", L"..\\Resources\\Animation\\Alchemist\\Alchemist_idle.anim");
	shared_ptr<Animation> pWalkAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Alchemist_Walk", L"..\\Resources\\Animation\\Alchemist\\Alchemist_walk.anim");
	shared_ptr<Animation> pAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Alchemist_Attack", L"..\\Resources\\Animation\\Alchemist\\Alchemist_attack.anim");
	shared_ptr<Animation> pWeakHitAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Alchemist_Weak_Hit", L"..\\Resources\\Animation\\Alchemist\\Alchemist_weak_hit.anim");
	pAlchemist->GetAnimator()->AddAnimation(L"Alchemist_Idle", pIdleAnimation);
	pAlchemist->GetAnimator()->AddAnimation(L"Alchemist_Walk", pWalkAnimation);
	pAlchemist->GetAnimator()->AddAnimation(L"Alchemist_Attack", pAttackAnimation);
	pAlchemist->GetAnimator()->AddAnimation(L"Alchemist_Weak_Hit", pWeakHitAnimation);
	pAlchemist->GetAnimator()->Play(L"Alchemist_Idle");

	pAttackAnimation->SetHitFrame(3);

	pAlchemist->UnflagAsAttacked();

	pAlchemist->GetTransform()->SetLocalPosition(vMonsterPos);
	return pAlchemist;
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

shared_ptr<Item> ObjectFactory::CreateItem(ITEM_KIND eItemKind)
{
	shared_ptr<Item> pItem = nullptr;
	switch (eItemKind)
	{
	case ITEM_KIND::FORBIDDEN_SWORD:
		pItem = CreateForbiddenSword();
		break;
	case ITEM_KIND::EVIL_SWORD_KIRION:
		pItem = CreateEvilSwordKirion();
		break;
	case ITEM_KIND::JENNYS_CHAIN_SICKLE:
		pItem = CreateJennysChainSickle();
		break;
	case ITEM_KIND::INVISIBLE_KNIFE:
		pItem = CreateInvisibleKnife();
		break;
	case ITEM_KIND::SWORD_OF_SUN:
		pItem = CreateSwordOfSun();
		break;
	case ITEM_KIND::RING_OF_MOON:
		pItem = CreateRingOfMoon();
		break;
	}

	assert(pItem);

	pItem->SetPlayer(m_pPlayer.lock());
	return pItem;
}

shared_ptr<Item> ObjectFactory::CreateForbiddenSword()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::FORBIDDEN_SWORD;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"ForbiddenSword_Vignette", L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"ForbiddenSword", L"..\\Resources\\Texture\\Item\\ForbiddenSword\\Image_ForbiddenSword.png");
	
	itemInfo.eGrade = GRADE::UNIQUE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();
	
	itemInfo.szName = L"봉인된 검";
	itemInfo.szComment = L"강력한 힘으로 억제되어 있는 검. 미세한 떨림이 느껴진다.";
	itemInfo.szExplanation = L"물리공격력이 15% 증가합니다.\n300명의 적 처치 시 이 아이템은 '마검: 키리온'으로 변합니다";

	shared_ptr<Item> pForbiddenSword = make_shared<ForbiddenSword>(itemInfo);

	return pForbiddenSword;
}

shared_ptr<Item> ObjectFactory::CreateEvilSwordKirion()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::EVIL_SWORD_KIRION;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"EvilSwordKirion_Vignette", L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"EvilSwordKirion", L"..\\Resources\\Texture\\Item\\EvilSwordKirion\\Image_EvilSwordKirion.png");
	
	itemInfo.eGrade = GRADE::LEGENDARY;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"마검: 키리온";
	itemInfo.szComment = L"생명력을 흡수하는 저주받은 마검, 피가 흐르는 이는 절대로 지닐 수 없다.";
	itemInfo.szExplanation = L"물리공격력이 60% 증가합니다.\n기본공격 및 대쉬 시 참격이 발생하여 물리데미지를 입힙니다.";

	shared_ptr<Item> pDemonSwordKirion = make_shared<EvilSwordKirion>(itemInfo);

	return pDemonSwordKirion;
}

shared_ptr<Item> ObjectFactory::CreateJennysChainSickle()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::JENNYS_CHAIN_SICKLE;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"JennysChainSickle_Vignette", L"..\\Resources\\Texture\\Item\\JennysChainSickle\\Image_JennysChainSickle_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"JennysChainSickle", L"..\\Resources\\Texture\\Item\\JennysChainSickle\\Image_JennysChainSickle.png");

	itemInfo.eGrade = GRADE::RARE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"제니의 사슬낫";
	itemInfo.szComment = L"처음 뵙겠어요 오라버니. 하지만 여기까지에요.";
	itemInfo.szExplanation = L"공중에서 기본공격 시 사슬낫을 휘둘러 물리데미지를 입힙니다.";

	shared_ptr<Item> pJennysChainSickle = make_shared<JennysChainSickle>(itemInfo);

	return pJennysChainSickle;
}

shared_ptr<Item> ObjectFactory::CreateInvisibleKnife()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::INVISIBLE_KNIFE;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"InvisibleKnife_Vignette", L"..\\Resources\\Texture\\Item\\InvisibleKnife\\Image_InvisibleKnife_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"InvisibleKnife", L"..\\Resources\\Texture\\Item\\InvisibleKnife\\Image_InvisibleKnife.png");

	itemInfo.eGrade = GRADE::RARE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"보이지 않는 검";
	itemInfo.szComment = L"날이 보이지 않는 검. 누군가 찔리면 영혼이 다친다고 한다.";
	itemInfo.szExplanation = L"치명타 시 보이지 않는 검으로 찔러 추가 마법데미지를 입힙니다.\n치명타 확률이 10 % 증가합니다.";

	shared_ptr<Item> pInvisibleKnife = make_shared<InvisibleKnife>(itemInfo);

	return pInvisibleKnife;
}

shared_ptr<Item> ObjectFactory::CreateRingOfMoon()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::RING_OF_MOON;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"RingOfMoon_Vignette", L"..\\Resources\\Texture\\Item\\RingOfMoon\\Image_RingOfMoon_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"RingOfMoon", L"..\\Resources\\Texture\\Item\\RingOfMoon\\Image_RingOfMoon.png");

	itemInfo.eGrade = GRADE::RARE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"달의 반지";
	itemInfo.szComment = L"누군가를 기다리는 듯한, 달의 문양이 새겨진 반지.";
	itemInfo.szExplanation = L"마법공격력이 40% 증가합니다.";

	shared_ptr<Item> pRingOfMoon = make_shared<RingOfMoon>(itemInfo);

	return pRingOfMoon;
}

shared_ptr<Item> ObjectFactory::CreateSwordOfSun()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::SWORD_OF_SUN;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"SwordOfSun_Vignette", L"..\\Resources\\Texture\\Item\\SwordOfSun\\Image_SwordOfSun_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"SwordOfSun", L"..\\Resources\\Texture\\Item\\SwordOfSun\\Image_SwordOfSun.png");

	itemInfo.eGrade = GRADE::RARE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"태양의 검";
	itemInfo.szComment = L"무언가를 그리워하는 듯한, 태양의 문양이 새겨진 검.";
	itemInfo.szExplanation = L"물리공격력이 40% 증가합니다.";

	shared_ptr<Item> pSwordOfSun = make_shared<SwordOfSun>(itemInfo);

	return pSwordOfSun;
}

shared_ptr<Item> ObjectFactory::CreateBoneOfMana()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::BONE_OF_MANA;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"BoneOfMana_Vignette", L"..\\Resources\\Texture\\Item\\BoneOfMana\\Image_BoneOfMana_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"BoneOfMana", L"..\\Resources\\Texture\\Item\\BoneOfMana\\Image_BoneOfMana.png");

	itemInfo.eGrade = GRADE::UNIQUE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"마나의 뼈";
	itemInfo.szComment = L"대체 어떤 부유한 스켈레톤이 이런걸 만들어서 쓸까?";
	itemInfo.szExplanation = L"스킬 사용 시 자신을 감싸는 마나 폭풍을 일으켜 마법데미지를 입힙니다.\n보유한 밸런스 타입 스컬 개수에 따라 마나폭풍의 데미지와 범위가(20 % / 60 %) 증가합니다.";

	shared_ptr<Item> pBoneOfMana = make_shared<BoneOfMana>(itemInfo);

	return pBoneOfMana;
}

shared_ptr<Item> ObjectFactory::CreateThiefsBlackIronDaggers()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::THIEFS_BLACK_IRON_DAGGERS;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"ThiefsBlackIronDaggers_Vignette", L"..\\Resources\\Texture\\Item\\ThiefsBlackIronDaggers\\Image_ThiefsBlackIronDaggers_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"ThiefsBlackIronDaggers", L"..\\Resources\\Texture\\Item\\ThiefsBlackIronDaggers\\Image_ThiefsBlackIronDaggers.png");

	itemInfo.eGrade = GRADE::UNIQUE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"도적의 흑철단검";
	itemInfo.szComment = L"빛의 흡수력이 뛰어난 흑철로 만들어 어둠 속에서는 잘 보이지 않는다.";
	itemInfo.szExplanation = L"적을 공격할 때마다 2초간 치명타 확률이 2% 증가합니다.\n이 효과는 20회까지 중첩됩니다.";

	shared_ptr<Item> pThiefsBlackIronDaggers = make_shared<ThiefsBlackIronDaggers>(itemInfo);

	return pThiefsBlackIronDaggers;
}

shared_ptr<Item> ObjectFactory::CreateGunpowderSword()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::GUNPOWDER_SWORD;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"GunpowderSword_Vignette", L"..\\Resources\\Texture\\Item\\GunpowderSword\\Image_GunpowderSword_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"GunpowderSword", L"..\\Resources\\Texture\\Item\\GunpowderSword\\Image_GunpowderSword.png");

	itemInfo.eGrade = GRADE::UNIQUE;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"화약검";
	itemInfo.szComment = L"\"이걸 살 때만 해도 분명히 휘두르기만 하면 빵빵 터진다고 했다고!\"- 모험가 칼리반";
	itemInfo.szExplanation = L"치명타 시 폭발이 일어나 물리데미지를 입힙니다.";

	shared_ptr<Item> pGunpowderSword = make_shared<GunpowderSword>(itemInfo);
	return pGunpowderSword;
}

shared_ptr<Item> ObjectFactory::CreateRavenLordsFeather()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::RAVEN_LORDS_FEATHER;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"RavenLordsFeather_Vignette", L"..\\Resources\\Texture\\Item\\RavenLordsFeather\\Image_RavenLordsFeather_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"RavenLordsFeather", L"..\\Resources\\Texture\\Item\\RavenLordsFeather\\Image_RavenLordsFeather.png");

	itemInfo.eGrade = GRADE::LEGENDARY;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"까마귀 군주의 깃털";
	itemInfo.szComment = L"두 세계 간 원리 원칙과 존재의 밀도 차이가 흡입력을 만들어 낸다.";
	itemInfo.szExplanation = L"교대 시 주변 적들에게 마법데미지를 입히고 소용돌이의 중심으로 끌어당깁니다.";

	shared_ptr<Item> pRavenLordsFeather = make_shared<RavenLordsFeather>(itemInfo);
	return pRavenLordsFeather;
}

shared_ptr<Item> ObjectFactory::CreateVoodooDoll()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::VOODOO_DOLL;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"VoodooDoll_Vignette", L"..\\Resources\\Texture\\Item\\VoodooDoll\\Image_VoodooDoll_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"VoodooDoll", L"..\\Resources\\Texture\\Item\\VoodooDoll\\Image_VoodooDoll.png");

	itemInfo.eGrade = GRADE::LEGENDARY;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"부두 인형";
	itemInfo.szComment = L"저주받은 자여, 그대는 죽어도 죽지 못해 영원토록 구천을 떠돌게 될 것이다.";
	itemInfo.szExplanation = L"죽음에 이르는 데미지를 입을 시 40의 체력을 회복하고 죽음을 극복하며 부두 인형이 찢어집니다.";

	shared_ptr<Item> pVoodooDoll = make_shared<VoodooDoll>(itemInfo);
	return pVoodooDoll;
}

shared_ptr<Item> ObjectFactory::CreateBrightDawn()
{
	ItemInfo itemInfo = {};
	itemInfo.eItemKind = ITEM_KIND::BRIGHT_DAWN;
	itemInfo.pVignetteTexture = GET_SINGLE(Resources)->Load<Texture>(L"BrightDawn_Vignette", L"..\\Resources\\Texture\\Item\\BrightDawn\\Image_BrightDawn_Vignette.png");
	itemInfo.pItemTexture = GET_SINGLE(Resources)->Load<Texture>(L"BrightDawn", L"..\\Resources\\Texture\\Item\\BrightDawn\\Image_BrightDawn.png");

	itemInfo.eGrade = GRADE::LEGENDARY;
	itemInfo.pFirstEngrave = make_shared<Arms>();
	itemInfo.pSecondEngrave = make_shared<Rapidity>();

	itemInfo.szName = L"찬란한 여명";
	itemInfo.szComment = L"여명이 밝아오니, 예정 된 승리를 기다리리라";
	itemInfo.szExplanation = L"물리공격력 및 마법공격력이 80% 증가합니다.\n적 공격 시 여명의 빛이 일어나 물리와 마법 중 더 높은 공격력에 따라 주변 적에게 데미지를 입힙니다.(쿨타임 : 50초)";

	shared_ptr<Item> pBrightDawn = make_shared<BrightDawn>(itemInfo);
	return pBrightDawn;
}

shared_ptr<Essence> ObjectFactory::CreateLyweasel()
{
	EssenceInfo essenceInfo = {};
	essenceInfo.szName = L"라이위즐";
	essenceInfo.szSkillName = L"점멸";
	essenceInfo.szComment = L"너무 빨라서 마족 중 그 누구도 정체를 알 수 없었던 정령 일족";
	essenceInfo.szExplanation = L"라이위즐이 나타나 번개를 내리쳐 마법데미지를 입힙니다.\n대쉬거리가 30%증가하고 대쉬거리에 번개를 내리쳐 마법데미지를 입힙니다";
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

shared_ptr<Essence> ObjectFactory::CreateEssence(ESSENCE_KIND eEssenceKind)
{
	shared_ptr<Essence> pEssence = nullptr;

	switch (eEssenceKind)
	{
	case ESSENCE_KIND::LYWEASEL:
		pEssence = CreateLyweasel();
		break;
	case ESSENCE_KIND::WISP:
		pEssence = CreateWisp();
		break;
	}

	assert(pEssence);

	pEssence->SetPlayer(m_pPlayer.lock());
	return pEssence;
}