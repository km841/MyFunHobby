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

void Monster::AnimateHitEffect()
{
	shared_ptr<AnimationGlobalEffect> pHitEffect = AnimationGlobalEffect::Get();
	pHitEffect->AddComponent(make_shared<Animator>());
	pHitEffect->AddComponent(make_shared<Transform>());
	pHitEffect->GetTransform()->SetParent(GetTransform());
	Vec3 vEffectPos = pHitEffect->GetTransform()->GetLocalPosition();
	vEffectPos.z -= 0.5f;
	pHitEffect->GetTransform()->SetLocalPosition(vEffectPos);


	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pHitEffect->AddComponent(pMeshRenderer);

	// 애니메이션 추가


	pHitEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHitEffect, eSceneType));
}

void Monster::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void Monster::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

