#include "pch.h"
#include "EvilSwordKirion.h"
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
#include "KirionDashSlashEffect.h"


EvilSwordKirion::EvilSwordKirion(const ItemInfo& itemInfo)
	: Item(itemInfo)
	, m_fDepthValue(0.f)
{
}

EvilSwordKirion::~EvilSwordKirion()
{
}

void EvilSwordKirion::Awake()
{
	Item::Awake();
}

void EvilSwordKirion::Start()
{
	Item::Start();
}

void EvilSwordKirion::Update()
{
	Item::Update();
	if (50.f < m_fDepthValue)
		m_fDepthValue = 0.f;
}

void EvilSwordKirion::LateUpdate()
{
	Item::LateUpdate();
}

void EvilSwordKirion::FinalUpdate()
{
	Item::FinalUpdate();
}

void EvilSwordKirion::ActiveMethodWhenHitTiming()
{
	CreateSlashEffectAndAddedToScene();
}

void EvilSwordKirion::ActiveMethodWhenDashTiming()
{
	CreateDashEffectAndAddedToScene();
}

void EvilSwordKirion::CreateSlashEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pAnimationLocalEffect->SetDirection(m_pPlayer.lock()->GetDirection());

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= (10.f + m_fDepthValue++);

	uint8 iDirection = static_cast<uint8>(m_pPlayer.lock()->GetDirection());
	vPlayerPos.x += iDirection ? -30.f : 30.f;

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());

	wstring szRandomAnim = {};
	szRandomAnim.push_back(RANDOM('a', 'd'));
	szRandomAnim += L".anim";

	// Kirion Slash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Kirion_Slash", L"..\\Resources\\Animation\\Item\\Kirion\\kirion_slash_" + szRandomAnim);
		pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Kirion_Slash", pAnimation);
	}

	pAnimationLocalEffect->GetAnimator()->Play(L"Kirion_Slash", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}

void EvilSwordKirion::CreateDashEffectAndAddedToScene()
{
	shared_ptr<KirionDashSlashEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<KirionDashSlashEffect>(L"Forward");
	pAnimationLocalEffect->SetDirection(m_pPlayer.lock()->GetDirection());

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= (10.f + m_fDepthValue++);

	float fRandomDegree = static_cast<float>(RANDOM(0, 360));
	float fRandomRadian = fRandomDegree * XM_PI / 180.f;

	pAnimationLocalEffect->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRandomRadian));

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPlayerPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));


	pAnimationLocalEffect->AddComponent(make_shared<Animator>());

	// Kirion Dash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Kirion_Slash_Dash", L"..\\Resources\\Animation\\Item\\Kirion\\kirion_slash_dash.anim");
		pAnimationLocalEffect->GetAnimator()->AddAnimation(L"Kirion_Slash_Dash", pAnimation);
		pAnimation->SetHitFrame(3);
	}

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}
