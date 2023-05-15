#include "pch.h"
#include "Monster.h"
#include "Transform.h"
#include "Physical.h"
#include "Clock.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "AnimationGlobalEffect.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Resources.h"
#include "MonsterHPHUD.h"
#include "ObjectFactory.h"
#include "MonsterHealthBarShowScript.h"
#include "ObjectRemoveToSceneEvent.h"
#include "AnimationLocalEffect.h"
#include "ObjectReturnToPoolEvent.h"
#include "ParticleSystem.h"


Monster::Monster()
	: GameObject(LAYER_TYPE::MONSTER)
	, m_bExtraHitFlag(false)
	, m_bHitFlag(false)
{
}

Monster::~Monster()
{
}

void Monster::Awake()
{
	GameObject::Awake();
	m_Status.MonsterDefaultSetting();
	CreateMonsterHPHUD();
	CreateParticleGeneratorAndAddedToScene();
}

void Monster::Start()
{
	GameObject::Start();
}

void Monster::Update()
{
	GameObject::Update();
}

void Monster::LateUpdate()
{
	GameObject::LateUpdate();
}

void Monster::FinalUpdate()
{
	GameObject::FinalUpdate();
}


void Monster::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void Monster::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

int32 Monster::CalculateParticleDirectionToDegree(PARTICLE_DIRECTION eParticleDirection)
{
	switch (eParticleDirection)
	{
	case PARTICLE_DIRECTION::TOP:
		return RANDOM(75, 105);
	case PARTICLE_DIRECTION::RIGHT_TOP:
		return RANDOM(60, 90);
	case PARTICLE_DIRECTION::RIGHT:
		return RANDOM(60, 90);
	case PARTICLE_DIRECTION::RIGHT_BTM:
		return RANDOM(-30, -60);
	case PARTICLE_DIRECTION::BTM:
		return RANDOM(-75, -105);
	case PARTICLE_DIRECTION::LEFT_BTM:
		return RANDOM(120, 150);
	case PARTICLE_DIRECTION::LEFT:
		return RANDOM(-240, -270);
	case PARTICLE_DIRECTION::LEFT_TOP:
		return RANDOM(-240, -270);
	}

	return 0;
}

void Monster::CreateMonsterHPHUD()
{
	m_pMonsterHPHUDFrame = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MonsterHPHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar_Frame.png", Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUDFrame->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUDFrame->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -1.f));

	m_pMonsterHPHUDFrame->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));

	m_pMonsterHPHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MonsterHPHUD>(L"MonsterHP", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar.png",  Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUD->AddComponent(make_shared<MonsterHealthBarShowScript>(m_pMonsterHPHUD));
	m_pMonsterHPHUD->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUD->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -2.f));
	m_pMonsterHPHUD->GetTransform()->SetLocalScale(Vec3(30.f, 3.f, 1.f));

	m_pMonsterHPHUD->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::CreateDeadEffectAndAddedScene()
{
	shared_ptr<AnimationLocalEffect> pDeadEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pDeadEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Monster_Dead", L"..\\Resources\\Animation\\MonsterCommon\\monster_dead.anim");
	pDeadEffect->GetAnimator()->AddAnimation(L"Monster_Dead", pDeadAnimation);
	pDeadEffect->GetAnimator()->Play(L"Monster_Dead", false);

	pDeadEffect->GetTransform()->SetLocalPosition(GetTransform()->GetPhysicalPosition());
	pDeadEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDeadEffect, eSceneType));
}

void Monster::CreateParticleGeneratorAndAddedToScene()
{
	m_pParticleGenerator = make_shared<GlobalEffect>();
	m_pParticleGenerator->AddComponent(make_shared<Transform>());
	m_pParticleGenerator->GetTransform()->SetParent(GetTransform());
	m_pParticleGenerator->AddComponent(make_shared<ParticleSystem>());
	m_pParticleGenerator->SetFrustum(false);

	m_pParticleGenerator->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pParticleGenerator, eSceneType));
}

void Monster::ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection)
{
	ScatterParticles(eParticleDirection);
	
	CreateDeadEffectAndAddedScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::ActivateDeadEvent(const Vec3& vDir)
{
	ScatterParticles(vDir);

	CreateDeadEffectAndAddedScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}
