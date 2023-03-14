#include "pch.h"
#include "PxDispatcher.h"
#include "ContactCallback.h"

PxDispatcher::PxDispatcher()
	: m_pCpuDispatcher(nullptr)
	, m_pCallback(nullptr)
{
	m_pCallback = new ContactCallback;
}

PxDispatcher::~PxDispatcher()
{
	if (m_pCpuDispatcher)
		m_pCpuDispatcher->release();

	if (m_pCallback)
	{
		delete m_pCallback;
		m_pCallback = nullptr;
	}
}

void PxDispatcher::CreateCpuDispatcher()
{
	m_pCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
}
