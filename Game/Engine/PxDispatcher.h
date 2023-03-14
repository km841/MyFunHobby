#pragma once

class ContactCallback;

class PxDispatcher
{
public:
	PxDispatcher();
	~PxDispatcher();

public:
	PxDefaultCpuDispatcher* GetCpuDispatcher() { return m_pCpuDispatcher; }
	ContactCallback*		GetSimulationCallback() { return m_pCallback; }
	void					CreateCpuDispatcher();

private:
	PxDefaultCpuDispatcher* m_pCpuDispatcher;
	ContactCallback*		m_pCallback;
};
