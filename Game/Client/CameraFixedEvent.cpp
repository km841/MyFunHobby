#include "pch.h"
#include "CameraFixedEvent.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "Scene.h"
#include "Scenes.h"
#include "Transform.h"

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
	const Vec3& vCameraPos = GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetTransform()->GetLocalPosition();
	GET_SINGLE(Scenes)->GetActiveScene()->GetMainCamera().lock()->GetCamera()->SetFixedCamera(m_vFixedPos == Vec3::Zero ? vCameraPos : m_vFixedPos);
}
