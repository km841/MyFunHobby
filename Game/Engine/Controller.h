#pragma once
#include "Component.h"
class Controller :
    public Component
{
public:
	Controller();
	virtual ~Controller();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

public:
	void Move(const PxVec3& vVec, PxQueryFilterCallback* pCallback, PxFilterData filtData);

private:
	PxControllerFilters m_CtlFilters;
};

