#include "pch.h"
#include "LittleBoneHead.h"
#include "RigidBody.h"
#include "LittleBone.h"

LittleBoneHead::LittleBoneHead(shared_ptr<LittleBone> pLittleBone)
	:m_pLittleBone(pLittleBone)
{
}

LittleBoneHead::~LittleBoneHead()
{
}

void LittleBoneHead::Awake()
{
	PlayerProjectile::Awake();
}

void LittleBoneHead::Start()
{
	PlayerProjectile::Start();
}

void LittleBoneHead::Update()
{
	PlayerProjectile::Update();
	//if (Vec3::Zero == m_vVelocity)
	//	return;
	//GetRigidBody()->SetVelocity(m_vVelocity);
}

void LittleBoneHead::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void LittleBoneHead::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

void LittleBoneHead::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void LittleBoneHead::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void LittleBoneHead::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
	{
		int a = 0;
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void LittleBoneHead::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
