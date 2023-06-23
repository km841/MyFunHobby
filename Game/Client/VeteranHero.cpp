#include "pch.h"
#include "VeteranHero.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "ObjectFactory.h"
#include "Resources.h"
#include "LocalEffect.h"
#include "AnimationLocalEffect.h"
#include "ObjectReturnToPoolEvent.h"
#include "VeteranHeroDeadObject.h"

#include "ComponentObject.h"
#include "SoundSource.h"

VeteranHero::VeteranHero()
	: m_bLandingFlag(false)
	, m_bLandingChecked(false)
	, m_bGroundFlag(false)
{
	SetMonsterState(MONSTER_STATE::PATROL);
	m_eMonsterType = MONSTER_TYPE::NONE_HIT;
}

VeteranHero::~VeteranHero()
{
}

void VeteranHero::Awake()
{
	GameObject::Awake();
	CreateStingerEffectAndAddedToScene();
	CreateParticleGeneratorAndAddedToScene();
	m_Status.BossMonsterDefaultSetting();
}

void VeteranHero::Start()
{
	GameObject::Start();
}

void VeteranHero::Update()
{
	GameObject::Update();
	ReorganizePosition();
	ReorganizePosition();

	if (m_bLandingFlag)
	{
		if (!m_bLandingChecked)
		{
			GetRigidBody()->SetVelocity(Vec3::Zero);
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetLinearMaxVelocityForDynamic(2000.f);
			m_bLandingChecked = true;
			SetMonsterState(MONSTER_STATE::LANDING);
			GetAnimator()->Play(L"VeteranHero_Landing", false);

			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Hero_Landing", L"..\\Resources\\Sound\\AdventurerHero_HeroLanding_Wind.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
		}
	}

}

void VeteranHero::LateUpdate()
{
	GameObject::LateUpdate();
}

void VeteranHero::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void VeteranHero::Destroy()
{

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(m_pStingerEffect.lock(), eSceneType));
}

void VeteranHero::CreateStingerSlashEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pAnimationLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	pAnimationLocalEffect->SetDirection(GetDirection());
	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.z -= -0.5f;

	pAnimationLocalEffect->GetTransform()->SetLocalPosition(vPos);
	pAnimationLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pAnimationLocalEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"StingerSlashEffect", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_stinger_slash_effect.anim");
	pAnimationLocalEffect->GetAnimator()->AddAnimation(L"StingerSlashEffect", pAnimation);
	pAnimationLocalEffect->GetAnimator()->Play(L"StingerSlashEffect", false);

	pAnimationLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAnimationLocalEffect, eSceneType));
}

void VeteranHero::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bLandingFlag = true;
		m_bGroundFlag = true;
	}
}

void VeteranHero::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bGroundFlag = false;
	}
}

void VeteranHero::SetStingerEffectState(bool bState)
{
	if (bState)
		m_pStingerEffect.lock()->Enable();
	else
		m_pStingerEffect.lock()->Disable();
}

void VeteranHero::ActivateDeadEvent()
{
	if (m_pStingerEffect.lock())
		m_pStingerEffect.lock()->Disable();
	CreateDeadObjectAndAddedToScene();

	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Hero_Dead", L"..\\Resources\\Sound\\AdventurerHero_Voice_Dead.wav");
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->Play();
}

void VeteranHero::CreateStingerEffectAndAddedToScene()
{
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<LocalEffect>(L"Forward");
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	pLocalEffect->GetTransform()->SetParent(GetTransform());
	pLocalEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -0.5f));
	//pLocalEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pLocalEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"StingerEffect", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_stinger_effect.anim");
	pLocalEffect->GetAnimator()->AddAnimation(L"StingerEffect", pAnimation);
	pLocalEffect->GetAnimator()->Play(L"StingerEffect");

	pLocalEffect->Awake();
	pLocalEffect->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));

	m_pStingerEffect = pLocalEffect;
}

void VeteranHero::CreateDeadObjectAndAddedToScene()
{
	shared_ptr<VeteranHeroDeadObject> pDeadObject = 
		GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VeteranHeroDeadObject>(L"Forward", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(10.f, 10.f, 1.f), MassProperties(), L"..\\Resources\\Texture\\Sprites\\VeteranHero\\Sprite_VeteranHero_Dead.png");
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.z -= 0.5f;
	vPos.y += 20.f;

	pDeadObject->GetTransform()->SetLocalPosition(vPos);
	pDeadObject->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDeadObject, eSceneType));
}
