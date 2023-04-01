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
	m_pStateMachine->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	m_pActiveSkul->Awake();
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
		m_arrSkuls[static_cast<uint8>(SKUL_POS::FIRST)] = pSkul;
		m_pActiveSkul = pSkul;
		m_pActiveSkul->SetSkulPos(SKUL_POS::FIRST);
		m_pActiveSkul->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	}

	else if (!m_arrSkuls[static_cast<uint8>(SKUL_POS::SECOND)])
	{
		m_arrSkuls[static_cast<uint8>(SKUL_POS::SECOND)] = pSkul;
		pSkul->SetSkulPos(SKUL_POS::SECOND);
		pSkul->SetPlayer(Conv::BaseToDeclare<Player>(shared_from_this()));
	}

	else
	{
		shared_ptr<Skul> pDropSkul = m_pActiveSkul;
		pSkul->SetSkulPos(pDropSkul->GetSkulPos());
		m_pActiveSkul = pSkul;
		return pDropSkul;
	}

	return nullptr;
}

void Player::SwapSkul()
{
	if (!m_arrSkuls[static_cast<uint8>(SKUL_POS::SECOND)])
		return;

	SKUL_POS eSkulPos = m_pActiveSkul->GetSkulPos();
	switch (eSkulPos)
	{
	case SKUL_POS::FIRST:
		m_pActiveSkul = m_arrSkuls[static_cast<uint8>(SKUL_POS::SECOND)];
		break;
	case SKUL_POS::SECOND:
		m_pActiveSkul = m_arrSkuls[static_cast<uint8>(SKUL_POS::FIRST)];
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
