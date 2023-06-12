#include "pch.h"
#include "CameraFixedEvent.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Scenes.h"

CameraFixedEvent::CameraFixedEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vFixedPos)
	: DungeonEvent(DUNGEON_EVENT_KIND::CAMERA_FIXED, pConditionBlock)
	, m_vFixedPos(vFixedPos)
{
}

CameraFixedEvent::~CameraFixedEvent()
{
}

void CameraFixedEvent::Update()
{
	DungeonEvent::Update();
}

void CameraFixedEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->SetFixedCamera(m_vFixedPos);
}
