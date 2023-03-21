#include "pch.h"
#include "Controller.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GameObject.h"
#include "Engine.h"
#include "Timer.h"
#include "Transform.h"
#include "Physical.h"


Controller::Controller()
	: Component(COMPONENT_TYPE::CONTROLLER)
{
	m_CtlFilters = {};
}

Controller::~Controller()
{
}

void Controller::Awake()
{
	
}

void Controller::Start()
{
}

void Controller::Update()
{
}

void Controller::LateUpdate()
{
}

void Controller::FinalUpdate()
{
}

void Controller::Move(const PxVec3& vVec, PxQueryFilterCallback* pCallback, PxFilterData filtData)
{
	m_CtlFilters.mFilterCallback = pCallback;
	m_CtlFilters.mFilterData = &filtData;
	//PxTransform transform =GetPhysical()->GetController()->getActor()->getGlobalPose();
	//transform.q.z = 0.f;
	//GetPhysical()->GetController()->getActor()->setGlobalPose(transform);
	PxController* controller = GetPhysical()->GetController();
	if (controller)
	{
		controller->move(vVec, 0.001f, DELTA_TIME, m_CtlFilters);
	}
}
