#include "pch.h"
#include "DisableCameraTrackingEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "Camera.h"
#include "ComponentObject.h"

DisableCameraTrackingEvent::DisableCameraTrackingEvent(shared_ptr<ConditionBlock> pConditionBlock)
	: DungeonEvent(DUNGEON_EVENT_KIND::ENABLE_CAMERA_TRACKING, pConditionBlock)
{
}

DisableCameraTrackingEvent::~DisableCameraTrackingEvent()
{
}

void DisableCameraTrackingEvent::Update()
{
	DungeonEvent::Update();
}

void DisableCameraTrackingEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->DisableTracking();
}
