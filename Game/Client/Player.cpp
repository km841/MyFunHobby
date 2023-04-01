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

Player::Player()
	: GameObject(LAYER_TYPE::PLAYER)
	, m_ePlayerState(PLAYER_STATE::IDLE)
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
	m_pActiveSkul->Awake();

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
