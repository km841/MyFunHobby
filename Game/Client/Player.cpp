#include "pch.h"
#include "Player.h"
#include "PlayerState.h"
#include "StateMachine.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Transform.h"
#include "Collider.h"
#include "PlayerInterfaceHUD.h"

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

	shared_ptr<GameObject> pParent = shared_from_this();
	m_pStateMachine->SetPlayer(static_pointer_cast<Player>(pParent));

	m_pStateMachine->Awake();
}

void Player::Start()
{
	GameObject::Start();
}

void Player::Update()
{
	GameObject::Update();
	m_pStateMachine->Update();
}

void Player::LateUpdate()
{
	GameObject::LateUpdate();
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Player::ChangePlayerState(PLAYER_STATE ePlayerState)
{
	m_pStateMachine->ChangePlayerState(ePlayerState);
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
