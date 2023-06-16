#include "pch.h"
#include "EnableCameraTrackingEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Camera.h"
#include "ComponentObject.h"

EnableCameraTrackingEvent::EnableCameraTrackingEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::ENABLE_CAMERA_TRACKING, pConditionBlock)
{
}

EnableCameraTrackingEvent::~EnableCameraTrackingEvent()
{
}

void EnableCameraTrackingEvent::Update()
{
	DungeonEvent::Update();
}

void EnableCameraTrackingEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->EnableTracking();
}
