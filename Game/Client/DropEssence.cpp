#include "pch.h"
#include "DropEssence.h"
#include "Transform.h"
#include "Clock.h"
#include "Input.h"
#include "Player.h"
#include "Scenes.h"
#include "ObjectFactory.h"
#include "Lyweasel.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"

DropEssence::DropEssence(ESSENCE_KIND eEssenceKind)
	: GameObject(LAYER_TYPE::DROP_ESSENCE)
	, m_eEssenceKind(eEssenceKind)
	, m_bIsCollisionWithPlayer(false)
{
}

DropEssence::~DropEssence()
{
}

void DropEssence::Awake()
{
	GameObject::Awake();
}

void DropEssence::Start()
{
	GameObject::Start();
}

void DropEssence::Update()
{
	GameObject::Update();
	
	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

	static float fWaveValue = 0.f;
	static float fAcc = 0.f;
	fAcc += DELTA_TIME;
	fWaveValue = sinf(fAcc) * 0.05f;
	GetTransform()->SetPhysicalPosition(Vec3(vMyPos.x, vMyPos.y + fWaveValue, vMyPos.z));

	if (m_bIsCollisionWithPlayer && IS_DOWN(KEY_TYPE::F))
	{
		weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
		pPlayer.lock()->ObtainEssence(GET_SINGLE(ObjectFactory)->CreateEssence<Lyweasel>());

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
	}
}

void DropEssence::LateUpdate()
{
	GameObject::LateUpdate();
}

void DropEssence::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DropEssence::CreateTouchEffectAddedToScene()
{
}

void DropEssence::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = true;
	}
}

void DropEssence::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		m_bIsCollisionWithPlayer = false;
	}
}
