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
	PxControllerFilters filters = {};

	filters.mFilterCallback = pCallback;
	filters.mFilterData = &filtData;
	PxController* controller = GetPhysical()->GetController();

	// vVec3는 이동 방향과 속도를 나타낸다
	if (controller)
	{
		controller->move(vVec, 0.001f, DELTA_TIME, filters);
	}
}
