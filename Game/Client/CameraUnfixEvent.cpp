#include "pch.h"
#include "CameraUnfixEvent.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Scenes.h"

CameraUnfixEvent::CameraUnfixEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::CAMERA_UNFIX, pConditionBlock)
{
}

CameraUnfixEvent::~CameraUnfixEvent()
{
}

void CameraUnfixEvent::Update()
{
	DungeonEvent::Update();
}

void CameraUnfixEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->UnfixCamera();
}
