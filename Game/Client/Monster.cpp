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

void Monster::ActivateDeadEvent()
{
	ScatterParticles();
}
