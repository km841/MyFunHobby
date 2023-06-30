#include "pch.h"
#include "Player.h"
#include "PlayerState.h"
#include "StateMachine.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Transform.h"
#include "Collider.h"
#include "PlayerInterfaceHUD.h"
#include "Skul.h"
#include "Cemetery.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "GlobalEffect.h"
#include "Scene.h"
#include "Scenes.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Animator.h"
#include "Animation.h"
#include "Clock.h"
#include "SkulThumnailHUD.h"
#include "InterfaceManager.h"
#include "Engine.h"
#include "PlayerHitHUD.h"
#include "Item.h"
#include "Essence.h"
#include "Monster.h"
#include "ComponentObject.h"
#include "SoundSource.h"

Player::Player()
	: GameObject(LAYER_TYPE::PLAYER)
	, m_ePlayerState(PLAYER_STATE::IDLE)
	, m_iJumpCount(2)
	, m_bSwapActiveFlag(false)
	, m_tSwapCooldown(5.f)
	, m_bPause(true)
{
	m_Status.PlayerDefaultSetting();
	m_pStateMachine = make_shared<StateMachine>();
}

Player::~Player()
{
}

void Player::Awake()
{
	GameObject::Awake();

	for (uint8 i = 0; i < MAX_SKULS; ++i)
	{
		if (m_arrSkuls[i])
		{
			m_arrSkuls[i]->Awake();
		}
	}

	CreateDashSmokeAndAddedToScene();
	CreateJumpSmokeAndAddedToScene();

	m_pStateMachine->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	m_pStateMachine->Awake();
}

void Player::Start()
{
	GameObject::Start();
	m_pActiveSkul->Start();
}

void Player::Update()
{
	GameObject::Update();
	m_pActiveSkul->Update();
	m_pStateMachine->Update();

	SwapCooldownUpdate();
	SkulCooldownUpdate();

	ItemUpdate();
}

void Player::LateUpdate()
{
	GameObject::LateUpdate();
	m_pActiveSkul->LateUpdate();
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
	m_pActiveSkul->FinalUpdate();
}

weak_ptr<PlayerState> Player::GetPlayerState()
{
	assert(m_pStateMachine->GetActiveState().lock());
	return m_pStateMachine->GetActiveState().lock();
}

void Player::ChangePlayerState(PLAYER_STATE ePlayerState)
{
	m_pStateMachine->ChangePlayerState(ePlayerState);
}

void Player::Disable()
{
	if (m_pActiveSkul)
		m_pActiveSkul->Disable();
}

void Player::Enable()
{
	if (m_pActiveSkul)
		m_pActiveSkul->Enable();
}


shared_ptr<Skul> Player::ObtainSkul(shared_ptr<Skul> pSkul)
{
	if (!m_pActiveSkul)
	{
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::FIRST)] = pSkul;
		m_pActiveSkul = pSkul;
		m_pActiveSkul->SetSkulIndex(SKUL_INDEX::FIRST);
		m_pActiveSkul->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	}

	else if (!m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)])
	{
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)] = pSkul;
		pSkul->SetSkulIndex(SKUL_INDEX::SECOND);
		pSkul->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	}

	else
	{
		shared_ptr<Skul> pDropSkul = m_pActiveSkul;
		pSkul->SetSkulIndex(pDropSkul->GetSkulIndex());
		pSkul->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
		m_arrSkuls[static_cast<uint8>(pDropSkul->GetSkulIndex())] = pSkul;
		m_pActiveSkul = pSkul;
		RefreshAnimation();
		return pDropSkul;
	}

	return nullptr;
}

shared_ptr<Item> Player::ObtainItem(shared_ptr<Item> pItem)
{
	ITEM_PLACE eItemPlace =	GetNearEmptyItemPlace();

	if (ITEM_PLACE::END == eItemPlace)
	{
		// Full!
		// Open SelectItemUI!
		assert(nullptr);
	}
	else
	{
		m_arrItems[static_cast<uint8>(eItemPlace)] = pItem;
	}

	return nullptr;
}

void Player::RemoveItem(shared_ptr<Item> pItem)
{
	for (int32 i = 0; i < m_arrItems.size(); ++i)
	{
		if (m_arrItems[i] == pItem)
		{
			m_arrItems[i].reset();
			m_arrItems[i] = nullptr;
			break;
		}
	}
}

void Player::SwapSkul()
{
	if (!m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)])
		return;

	SKUL_INDEX eSkulPos = m_pActiveSkul->GetSkulIndex();
	switch (eSkulPos)
	{
	case SKUL_INDEX::FIRST:
		m_pActiveSkul = m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)];
		break;
	case SKUL_INDEX::SECOND:
		m_pActiveSkul = m_arrSkuls[static_cast<uint8>(SKUL_INDEX::FIRST)];
		break;
	}

	m_tSwapCooldown.Start();
}

void Player::RefreshAnimation()
{
	m_pStateMachine->GetActiveState().lock()->PlayAnimation();
}

void Player::SkulCooldownUpdate()
{
	if (!m_arrSkuls[0] || !m_arrSkuls[1])
		return;

	SKUL_INDEX eSkulIndex = m_pActiveSkul->GetSkulIndex();
	switch (eSkulIndex)
	{
	case SKUL_INDEX::FIRST:
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)]->SkillCooldownUpdate();
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::SECOND)]->LateUpdate();
		break;
	case SKUL_INDEX::SECOND:
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::FIRST)]->SkillCooldownUpdate();
		m_arrSkuls[static_cast<uint8>(SKUL_INDEX::FIRST)]->LateUpdate();
		break;
	}
}

void Player::SwapCooldownUpdate()
{
	if (!IsSwapPossible())
	{
		m_tSwapCooldown.Update(OBJECT_DELTA_TIME);
		if (IsSwapPossible())
		{
			weak_ptr<Interface> pInterface = GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::PLAYER_SKUL_THUMNAIL);
			if (pInterface.lock())
			{
				static_pointer_cast<SkulThumnailHUD>(pInterface.lock())->PlayCompletionAnimation();
			}
		}
	}
}

void Player::TakeDamage(uint32 iDamage)
{
	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"hit_blood", L"..\\Resources\\Sound\\hit_blood.wav");
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->Play();

	m_Status.TakeDamage(iDamage);
	static_pointer_cast<PlayerHitHUD>(GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::PLAYER_HIT))->PlayHitAnimation();
}

void Player::ActiveItemWhenHitTiming()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->ActiveMethodWhenHitTiming();
	}
}

void Player::ActiveItemWhenDashTiming()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->ActiveMethodWhenDashTiming();
	}
}

void Player::ActiveItemWhenJumpAttackEnterTiming()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->ActiveItemWhenJumpAttackEnterTiming();
	}
}

void Player::ActiveItemWhenMonsterKillTiming()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->ActiveItemWhenMonsterKillTiming();
	}
}

void Player::ActiveItemWhenMonsterHitTiming(shared_ptr<Monster> pMonster)
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->ActiveItemWhenMonsterHitTiming(pMonster);
	}
}

shared_ptr<Essence> Player::ObtainEssence(shared_ptr<Essence> pEssence)
{
	if (m_pEssence)
	{
		shared_ptr<Essence> pDropEssence = m_pEssence;
		m_pEssence = pEssence;
		return pDropEssence;
	}

	else
	{
		m_pEssence = pEssence;
	}

	return nullptr;
}

void Player::EssenceUpdate()
{
	if (m_pEssence)
		m_pEssence->Update();
}

weak_ptr<Essence> Player::GetEssence()
{
	return m_pEssence;
}

void Player::ActiveEssenceWhenDashEnterTiming()
{
	if (m_pEssence)
		m_pEssence->ActiveMethodWhenDashEnterTiming();
}

ITEM_PLACE Player::GetNearEmptyItemPlace()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (!m_arrItems[i])
			return static_cast<ITEM_PLACE>(i);
	}
	return ITEM_PLACE::END;
}

weak_ptr<Item> Player::GetItem(ITEM_PLACE eItemPlace)
{
	assert(static_cast<uint8>(eItemPlace) < MAX_ITEMS);
	return m_arrItems[static_cast<uint8>(eItemPlace)];
}

std::vector<ITEM_KIND> Player::GetItemList()
{
	std::vector<ITEM_KIND> vItemKinds;

	for (int32 i = 0; i < m_arrItems.size(); ++i)
	{
		if (m_arrItems[i])
			vItemKinds.push_back(m_arrItems[i]->GetItemInfo().eItemKind);
	}

	return vItemKinds;
}

void Player::ItemUpdate()
{
	for (int32 i = 0; i < MAX_ITEMS; ++i)
	{
		if (m_arrItems[i])
			m_arrItems[i]->Update();
	}
}

void Player::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
	{
	}
}

void Player::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void Player::CreateDashSmokeAndAddedToScene()
{
	m_pDashSmoke = make_shared<GlobalEffect>();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pDashSmoke->AddComponent(make_shared<Transform>());
	m_pDashSmoke->GetTransform()->SetGlobalOffset(Vec2(0.f, 10.f));
	m_pDashSmoke->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DashSmoke_Small", L"..\\Resources\\Animation\\SkulCommon\\common_dashsmoke_small.anim");
	m_pDashSmoke->GetAnimator()->AddAnimation(L"DashSmoke_Small", pAnimation);
	
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	m_pDashSmoke->AddComponent(pMeshRenderer);
	
	m_pDashSmoke->Awake();
	m_pDashSmoke->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pDashSmoke, eSceneType));
}

void Player::CreateJumpSmokeAndAddedToScene()
{
	m_pJumpSmoke = make_shared<GlobalEffect>();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pJumpSmoke->AddComponent(make_shared<Transform>());
	m_pJumpSmoke->GetTransform()->SetGlobalOffset(Vec2(0.f, -20.f));
	m_pJumpSmoke->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(L"DoubleJumpSmoke", L"..\\Resources\\Animation\\SkulCommon\\common_doublejumpsmoke.anim");
	m_pJumpSmoke->GetAnimator()->AddAnimation(L"DoubleJumpSmoke", pAnimation);

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	m_pJumpSmoke->AddComponent(pMeshRenderer);

	m_pJumpSmoke->Awake();
	m_pJumpSmoke->Disable();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pJumpSmoke, eSceneType));
}
