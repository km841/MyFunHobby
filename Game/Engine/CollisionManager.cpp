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
	auto&& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(static_cast<LAYER_TYPE>(iFirst));
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
