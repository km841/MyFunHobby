#include "pch.h"
#include "JennysChainSickle.h"
#include "JennysChainSickleSlashEffect.h"
#include "Animator.h"
#include "ObjectFactory.h"
#include "Animation.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Transform.h"
#include "Player.h"
#include "Input.h"
#include "Skul.h"
#include "SkulAttack.h"

JennysChainSickle::JennysChainSickle(const ItemInfo& itemInfo)
	: Item(itemInfo)
{
}

JennysChainSickle::~JennysChainSickle()
{
}

void JennysChainSickle::Awake()
{
	Item::Awake();
}

void JennysChainSickle::Start()
{
	Item::Start();
}

void JennysChainSickle::Update()
{
	Item::Update();
}

void JennysChainSickle::LateUpdate()
{
	Item::LateUpdate();
}

void JennysChainSickle::FinalUpdate()
{
	Item::FinalUpdate();
}

void JennysChainSickle::ActiveItemWhenJumpAttackEnterTiming()
{
	shared_ptr<JennysChainSickleSlashEffect> pSlashEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<JennysChainSickleSlashEffect>(L"Forward");
	pSlashEffect->GetTransform()->SetParent(m_pPlayer.lock()->GetTransform());
	pSlashEffect->AddComponent(make_shared<Animator>());

	// Slash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"JennysChainSickle_Slash", L"..\\Resources\\Animation\\Item\\JennysChainSickle\\jennyschainsickle_slash.anim");
		pSlashEffect->GetAnimator()->AddAnimation(L"JennysChainSickle_Slash", pAnimation);
		pSlashEffect->GetAnimator()->Play(L"JennysChainSickle_Slash", false);
		pAnimation->SetHitFrame(1);
	}

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSlashEffect, eSceneType));
}
