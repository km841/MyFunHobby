#include "pch.h"
#include "PxEnvironmentSetting.h"

PxEnvironmentSetting::PxEnvironmentSetting()
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

void PxEnvironmentSetting::CreatePhysics()
{
	assert(m_pFoundation);
	m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, PxTolerancesScale());
}

