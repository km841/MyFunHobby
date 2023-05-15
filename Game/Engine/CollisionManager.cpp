#include "pch.h"
#include "CollisionManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"
#include "Player.h"
#include "Monster.h"
#include "Physical.h"
#include "Transform.h"
#include "EventManager.h"
#include "ForceOnObjectEvent.h"
#include "RigidBody.h"

void CollisionManager::SetCollisionGroup(LAYER_TYPE iFirst, LAYER_TYPE iSecond)
{
	m_arrColGroup[static_cast<int32>(iFirst)][static_cast<int32>(iSecond)] = true;
}

void CollisionManager::Update()
{
	for (int32 i = 0; i < LAYER_TYPE_COUNT; ++i)
	{
		for (int32 j = 0; j < LAYER_TYPE_COUNT; ++j)
		{
			if (m_arrColGroup[i][j])
			{
				SetCollisionFlag(i, j);
			}
		}
	}
}

void CollisionManager::SetCollisionFlag(int32 iFirst, int32 iSecond)
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(static_cast<LAYER_TYPE>(iFirst));
	for (const auto& pGameObject : vGameObjects)
	{
		if (pGameObject->GetCollider())
		{
			PxFilterData& filterData = pGameObject->GetCollider()->GetFilterData();
			if (filterData.word0 & (1 << iFirst))
			{
				filterData.word1 |= (1 << iSecond);
			}
		}
	}
}

void CollisionManager::SetForceInLayer(LAYER_TYPE eLayerType, const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse)
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(eLayerType);
	Vec3 vLeftTop = Vec3(vPos.x - vVolume.x / 2.f, vPos.y + vVolume.y / 2.f, 0.f);
	Vec3 vRightBtm = Vec3(vPos.x + vVolume.x / 2.f, vPos.y - vVolume.y / 2.f, 0.f);

	for (auto& pGameObject : vGameObjects)
	{
		Vec3 vObjectPos = pGameObject->GetTransform()->GetPhysicalPosition();

		if (vObjectPos.x > vLeftTop.x && vObjectPos.x < vRightBtm.x &&
			vObjectPos.y > vRightBtm.y && vObjectPos.y < vLeftTop.y)
		{
			float fRandomAngular = static_cast<float>(RANDOM(-10, 10));
			pGameObject->GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, fRandomAngular));

			Vec3 vRandomImpulse = vImpulse;
			vRandomImpulse.y = static_cast<float>(RANDOM(static_cast<int32>(vImpulse.y - 100.f), static_cast<int32>(vImpulse.y + 100.f)));

			if (vRandomImpulse.x < 1.f)
			{
				vRandomImpulse.x = static_cast<float>(RANDOM(-50, 50));
			}

			GET_SINGLE(EventManager)->AddEvent(make_unique<ForceOnObjectEvent>(pGameObject, Conv::Vec3ToPxVec3(vRandomImpulse)));
		}
	}
}

void CollisionManager::SetForceInLayerAndFollowPlayer(LAYER_TYPE eLayerType, const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse)
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(eLayerType);
	Vec3 vLeftTop = Vec3(vPos.x - vVolume.x / 2.f, vPos.y + vVolume.y / 2.f, 0.f);
	Vec3 vRightBtm = Vec3(vPos.x + vVolume.x / 2.f, vPos.y - vVolume.y / 2.f, 0.f);

	for (auto& pGameObject : vGameObjects)
	{
		Vec3 vObjectPos = pGameObject->GetTransform()->GetPhysicalPosition();

		if (vObjectPos.x > vLeftTop.x && vObjectPos.x < vRightBtm.x &&
			vObjectPos.y > vRightBtm.y && vObjectPos.y < vLeftTop.y)
		{
			float fRandomAngular = static_cast<float>(RANDOM(-10, 10));
			pGameObject->GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, fRandomAngular));

			Vec3 vRandomImpulse = vImpulse;
			vRandomImpulse.y = static_cast<float>(RANDOM(static_cast<int32>(vImpulse.y - 50.f), static_cast<int32>(vImpulse.y + 50.f)));

			if (vRandomImpulse.x < 1.f)
			{
				weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
				Vec3 vPlayerPos = pPlayer.lock()->GetTransform()->GetPhysicalPosition();

				Vec3 vDiff = vPlayerPos - vObjectPos;
				if (vDiff.x < 0.f)
				{
					vRandomImpulse.x = -fabs(vRandomImpulse.y);
				}
				else
				{
					vRandomImpulse.x = fabs(vRandomImpulse.y);
				}

				vRandomImpulse.x += static_cast<float>(RANDOM(-50, 50));
			}

			GET_SINGLE(EventManager)->AddEvent(make_unique<ForceOnObjectEvent>(pGameObject, Conv::Vec3ToPxVec3(vRandomImpulse)));
		}
	}
}
