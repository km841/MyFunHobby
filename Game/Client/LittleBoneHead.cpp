#include "pch.h"
#include "LittleBoneHead.h"
#include "RigidBody.h"
#include "LittleBone.h"
#include "Monster.h"
#include "Transform.h"
#include "Physical.h"
#include "Engine.h"
#include "Collider.h"
#include "Scene.h"
#include "Scenes.h"

LittleBoneHead::LittleBoneHead()
	: m_bTouch(false)
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

	if (m_bTouch)
	{
		GetRigidBody()->ApplyGravityForDynamic();
		//GET_SINGLE(Scenes)->GetActiveScene()->CameraShakeAxis(0.05f, Vec3(500.f, 0.f, 0.f));
		//PX_SCENE->GetScene()->removeActor(*GetPhysical()->GetActor());
		//PX_SCENE->GetScene()->flushSimulation();
	}
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
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType() ||
		LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		if (!m_bTouch)
			m_bTouch = true;
	}
}

void LittleBoneHead::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void LittleBoneHead::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{

}

void LittleBoneHead::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
