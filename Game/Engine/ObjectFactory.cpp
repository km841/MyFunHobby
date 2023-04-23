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

shared_ptr<Monster> ObjectFactory::CreateJuniorKnight(const Vec3& vMonsterPos)
{
	shared_ptr<JuniorKnight> pJuniorKnight = CreateObjectHavePhysicalFromPool<JuniorKnight>(L"Deferred", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 50.f), MassProperties(100.f, 100.f, 0.01f));
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
	shared_ptr<RemoveObjectTask> pRemoveTask = make_shared< RemoveObjectTask>(pJuniorKnight);

	pDeadSequence->AddChild(pDeadCondition);
	pDeadSequence->AddChild(pRemoveTask);

	pHitSequence->AddChild(pHitCondition);
	pHitSequence->AddChild(pRunHitAnimation);
	pHitSequence->AddChild(pDelayTask);

	pAttackSequence->AddChild(pNearCondition);
	pAttackSequence->AddChild(pRunAttackAnimation);

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

	pJuniorKnight->GetTransform()->SetLocalPosition(vMonsterPos);
	return pJuniorKnight;
}

void ObjectFactory::CreateSpawnEffectAndAddedScene(const Vec3& vMonsterPos)
{
	shared_ptr<AnimationLocalEffect> pSpawnEffect = CreateObjectHaveNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pSpawnEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pSpawnAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Monster_Spawn", L"..\\Resources\\Animation\\MonsterCommon\\monster_spawn.anim");
	pSpawnEffect->GetAnimator()->AddAnimation(L"Monster_Spawn", pSpawnAnimation);
	pSpawnEffect->GetAnimator()->Play(L"Monster_Spawn", false);

	pSpawnEffect->GetTransform()->SetLocalPosition(vMonsterPos);
	pSpawnEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSpawnEffect, eSceneType));
}
