#include "pch.h"
#include "IfTakedMapReward.h"
#include "MapReward.h"
#include "Scenes.h"
#include "Scene.h"

bool IfTakedMapReward::IsTrigger()
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::MAP_REWARD);
	assert(!vGameObjects.empty());

	return static_pointer_cast<MapReward>(vGameObjects[0])->IsTaked();
}
