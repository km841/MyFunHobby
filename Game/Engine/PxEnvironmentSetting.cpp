#include "pch.h"
#include "PxEnvironmentSetting.h"

PxEnvironmentSetting::PxEnvironmentSetting()
	: m_pFoundation(nullptr)
	, m_pPhysics(nullptr)
{
}

PxEnvironmentSetting::~PxEnvironmentSetting()
{
	if (m_pPhysics)
		m_pPhysics->release();

	if (m_pFoundation)
		m_pFoundation->release();
}

void PxEnvironmentSetting::CreateFoundation()
{
	m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_allocCallback, m_errorCallback);
}

void PxEnvironmentSetting::CreatePhysics(PxPvd* pPvd)
{
	assert(m_pFoundation);
	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale()/*, false, pPvd*/);
}