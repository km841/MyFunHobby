#include "pch.h"
#include "IfAllDeadMonsterInDungeon.h"
#include "Scene.h"
#include "Scenes.h"

bool IfAllDeadMonsterInDungeon::IsTrigger()
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::MONSTER);
	return vGameObjects.empty();
}
