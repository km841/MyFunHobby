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

Player::Player()
	: GameObject(LAYER_TYPE::PLAYER)
	, m_ePlayerState(PLAYER_STATE::IDLE)
	, m_iJumpCount(2)
	, m_bSwapActiveFlag(false)
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
	SkulCooldownUpdate();
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
		m_pActiveSkul = pSkul;
		return pDropSkul;
	}

	return nullptr;
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
}

void Player::RefreshAnimation()
{
	m_pStateMachine->GetActiveState().lock()->PlayAnimation();
}

void Player::SkulCooldownUpdate()
{
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

void Player::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

void Player::CreateDashSmokeAndAddedToScene()
{
	m_pDashSmoke = make_shared<GlobalEffect>();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();

	m_pDashSmoke->AddComponent(make_shared<Transform>());
	m_pDashSmoke->GetTransform()->SetGlobalOffset(Vec2(0.f, -10.f));
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
