#include "pch.h"
#include "Lyweasel.h"
#include "ObjectFactory.h"
#include "AnimationLocalEffect.h"
#include "Player.h"
#include "Animation.h"
#include "Animator.h"
#include "ObjectFollowScript.h"

Lyweasel::Lyweasel(const EssenceInfo& essenceInfo)
	: Essence(essenceInfo)
{
}

Lyweasel::~Lyweasel()
{
}

void Lyweasel::Awake()
{
}

void Lyweasel::Start()
{
}

void Lyweasel::Update()
{
}

void Lyweasel::LateUpdate()
{
}

void Lyweasel::FinalUpdate()
{
}

void Lyweasel::ActiveMethodWhenDashEnterTiming()
{
	CreateDashEffectAndAddedToScene();
}

void Lyweasel::CreateDashEffectAndAddedToScene()
{
	// 잔상 효과 (그 자리에서 효과 발현)
	CreateDashEffect();

	// 베리어 (플레이어 따라옴)
	CreateDashBarriorEffect();

}

void Lyweasel::CreateDashEffect()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pAnimationLocalEffect->SetDirection(m_pPlayer.lock()->GetDirection());

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= 5.f;

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());

	// Lyweasel_Dash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Lyweasel_Dash", L"..\\Resources\\Animation\\Essence\\Lyweasel\\lyweasel_dash.anim");
		pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Lyweasel_Dash", pAnimation);
	}

	pAnimationLocalEffect->GetAnimator()->Play(L"Lyweasel_Dash", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}

void Lyweasel::CreateDashBarriorEffect()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pAnimationLocalEffect->SetDirection(m_pPlayer.lock()->GetDirection());

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= 0.5f;

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	pAnimationLocalEffect->AddComponent(make_shared<ObjectFollowScript>(m_pPlayer.lock()));

	// Lyweasel_Dash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Lyweasel_Dash_Barrior", L"..\\Resources\\Animation\\Essence\\Lyweasel\\lyweasel_dash_barrior.anim");
		pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Lyweasel_Dash_Barrior", pAnimation);
	}

	pAnimationLocalEffect->GetAnimator()->Play(L"Lyweasel_Dash_Barrior", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}
