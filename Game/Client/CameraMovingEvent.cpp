#include "pch.h"
#include "CameraMovingEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "ComponentObject.h"
#include "Camera.h"

CameraMovingEvent::CameraMovingEvent(shared_ptr<ConditionBlock> pConditionBlock, const Vec3& vTargetPos, float fTime)
	: DungeonEvent(DUNGEON_EVENT_KIND::CAMERA_MOVING, pConditionBlock)
	, m_vTargetPos(vTargetPos)
	, m_fTime(fTime)
{
}

CameraMovingEvent::~CameraMovingEvent()
{
}

void CameraMovingEvent::Update()
{
	DungeonEvent::Update();
}

void CameraMovingEvent::ExecuteEvent()
{
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->SetTargetPos(m_vTargetPos, m_fTime);
}
