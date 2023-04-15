#include "pch.h"
#include "JuniorKnight.h"
#include "RigidBody.h"

POOL_INIT(JuniorKnight);
JuniorKnight::JuniorKnight()
{
}

JuniorKnight::~JuniorKnight()
{
}

void JuniorKnight::Awake()
{
	Monster::Awake();
}

void JuniorKnight::Start()
{
	Monster::Start();
}

void JuniorKnight::Update()
{
	Monster::Update();
	// 몬스터 AI 실행
}

void JuniorKnight::LateUpdate()
{
	Monster::LateUpdate();
}

void JuniorKnight::FinalUpdate()
{
	Monster::FinalUpdate();
}

void JuniorKnight::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void JuniorKnight::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void JuniorKnight::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
