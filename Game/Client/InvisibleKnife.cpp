#include "pch.h"
#include "InvisibleKnife.h"
#include "Animator.h"
#include "ObjectFactory.h"
#include "Animation.h"
#include "AnimationLocalEffect.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Transform.h"
#include "Player.h"
#include "Input.h"
#include "Skul.h"
#include "SkulAttack.h"
#include "Engine.h"

InvisibleKnife::InvisibleKnife(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

InvisibleKnife::~InvisibleKnife()
{
}

void InvisibleKnife::Awake()
{
	Item::Awake();
}

void InvisibleKnife::Start()
{
	Item::Start();
}

void InvisibleKnife::Update()
{
	Item::Update();
}

void InvisibleKnife::LateUpdate()
{
	Item::LateUpdate();
}

void InvisibleKnife::FinalUpdate()
{
	Item::FinalUpdate();
}

void InvisibleKnife::ActiveItemWhenMonsterHitTiming(shared_ptr<Monster> pMonster)
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	Vec3 vMonsterPos = pMonster->GetTransform()->GetPhysicalPosition();
	vMonsterPos.z -= 1.f;
	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vMonsterPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));
	pAnimationLocalEffect->AddComponent(make_shared<Animator>());

	float fRandomDegree = static_cast<float>(RANDOM(0, 360));
	float fRandomRadian = fRandomDegree * XM_PI / 180.f;

	pAnimationLocalEffect->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRandomRadian));

	// Invisible Knife Slash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Invisible_Knife_Slash", L"..\\Resources\\Animation\\Item\\InvisibleKnife\\invisibleknife_slash.anim");
		pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Invisible_Knife_Slash", pAnimation);
		pAnimationLocalEffect->GetAnimator()->Play(L"Invisible_Knife_Slash", false);
		pAnimation->SetHitFrame(1);
	}

	pMonster->GetStatus()->TakeDamage(static_cast<uint32>(1));
	if (!pMonster->GetStatus()->IsAlive())
	{
		pMonster->SetMonsterState(MONSTER_STATE::DEAD);
	}
	else
	{
		if (MONSTER_TYPE::NORMAL == pMonster->GetMonsterType())
			pMonster->SetMonsterState(MONSTER_STATE::WEAK_HIT);
		
		FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MAGIC, 1, vMonsterPos);
	}

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}
