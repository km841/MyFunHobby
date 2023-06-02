#include "pch.h"
#include "ForbiddenSword.h"
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

ForbiddenSword::ForbiddenSword(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

ForbiddenSword::~ForbiddenSword()
{
}

void ForbiddenSword::Awake()
{
	Item::Awake();
}

void ForbiddenSword::Start()
{
	Item::Start();
}

void ForbiddenSword::Update()
{
	Item::Update();
}

void ForbiddenSword::LateUpdate()
{
	Item::LateUpdate();
}

void ForbiddenSword::FinalUpdate()
{
	Item::FinalUpdate();
}

void ForbiddenSword::ActiveItemWhenMonsterKillTiming()
{
	m_pPlayer.lock()->ObtainItem(GET_SINGLE(ObjectFactory)->CreateItem<EvilSwordKirion>());

	shared_ptr<AnimationLocalEffect> pChangeEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pChangeEffect->GetTransform()->SetParent(m_pPlayer.lock()->GetTransform());
	pChangeEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 30.f, -0.5f));
	pChangeEffect->AddComponent(make_shared<Animator>());

	// Effect
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ForbiddenSword_Effect", L"..\\Resources\\Animation\\Item\\ForbiddenSword\\forbiddensword_maxstack.anim");
		pChangeEffect->GetAnimator()->AddAnimation(L"ForbiddenSword_Effect", pAnimation);
		pChangeEffect->GetAnimator()->Play(L"ForbiddenSword_Effect", false);
	}

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChangeEffect, eSceneType));

	m_pPlayer.lock()->RemoveItem(shared_from_this());
}
