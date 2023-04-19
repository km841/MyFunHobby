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
	CreateMonsterHPHUD();
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
	// HUD Size는 몬스터 종류에 따라 커질 수 있다.
	m_pMonsterHPHUDFrame = GET_SINGLE(ObjectFactory)->CreateObject<MonsterHPHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar_Frame.png", Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUDFrame->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUDFrame->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -1.f));

	m_pMonsterHPHUDFrame->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));

	m_pMonsterHPHUD = GET_SINGLE(ObjectFactory)->CreateObject<MonsterHPHUD>(L"HP", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar.png", Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUD->AddComponent(make_shared<MonsterHealthBarShowScript>(m_pMonsterHPHUD));
	m_pMonsterHPHUD->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUD->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -2.f));
	m_pMonsterHPHUD->GetTransform()->SetLocalScale(Vec3(30.f, 3.f, 1.f));

	m_pMonsterHPHUD->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection)
{
	ScatterParticles(eParticleDirection);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}
