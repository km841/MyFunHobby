#include "pch.h"
#include "Player.h"
#include "PlayerState.h"
#include "StateMachine.h"
#include "RigidBody.h"

Player::Player()
	: m_ePlayerState(PLAYER_STATE::IDLE)
{
	m_pStateMachine = make_unique<StateMachine>();
	m_eLayerType = LAYER_TYPE::PLAYER;
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

void Player::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void Player::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	GetRigidBody()->RemoveGravity();
	GetRigidBody()->SetVelocity(Vec3::Zero);
}

void Player::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	GetRigidBody()->ApplyGravity();
}
