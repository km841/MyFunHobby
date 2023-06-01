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
	Possession::Awake();
}

void LittleBoneHead::Start()
{
	Possession::Start();
}

void LittleBoneHead::Update()
{
	Possession::Update();

	if (m_bTouch)
	{
		GetRigidBody()->ApplyGravityForDynamic();
		//GET_SINGLE(Scenes)->GetActiveScene()->CameraShakeAxis(0.05f, Vec3(500.f, 0.f, 0.f));
		//PX_SCENE->GetScene()->removeActor(*GetPhysical()->GetActor());
		//PX_SCENE->GetScene()->flushSimulation();
	}
	else
	{
		uint8 iDirection = static_cast<uint8>(GetDirection());
		GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(iDirection ? -1000.f : 1000.f, 0.f, 0.f));
	}
}

void LittleBoneHead::LateUpdate()
{
	Possession::LateUpdate();
}

void LittleBoneHead::FinalUpdate()
{
	Possession::FinalUpdate();
}

void LittleBoneHead::Initialize()
{
	GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
	DisableTouchFlag();
}

void LittleBoneHead::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType() ||
		LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		if (!m_bTouch)
		{
			m_bTouch = true;

			if (LAYER_TYPE::MONSTER == pGameObject->GetLayerType())
			{
				weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(pGameObject);
				float fDamage = 4.f;
				pGameObject->GetStatus()->TakeDamage(static_cast<int32>(fDamage));

				Vec3 vMonsterPos = pMonster.lock()->GetTransform()->GetPhysicalPosition();
				if (!pGameObject->GetStatus()->IsAlive())
				{
					pMonster.lock()->SetMonsterState(MONSTER_STATE::DEAD);
					FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vMonsterPos);
				}
				else
				{
					if (MONSTER_TYPE::NORMAL == pMonster.lock()->GetMonsterType())
					{
						FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vMonsterPos);
						pMonster.lock()->SetMonsterState(MONSTER_STATE::WEAK_HIT);
					}

					else
					{
						FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vMonsterPos);
					}
				}
			}

			
			
		}
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
