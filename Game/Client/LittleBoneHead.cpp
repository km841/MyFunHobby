#include "pch.h"
#include "LittleBoneHead.h"
#include "RigidBody.h"
#include "LittleBone.h"
#include "Monster.h"
#include "Transform.h"

LittleBoneHead::LittleBoneHead()
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
}

void LittleBoneHead::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void LittleBoneHead::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
	{
		static_pointer_cast<Monster>(pGameObject)->FlagAsAttacked();
		// 몬스터와의 거리를 계산해서 힘 주기
		
	}

	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		int a = 0;
	}
}

void LittleBoneHead::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
