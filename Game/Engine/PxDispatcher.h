#pragma once

class ContactCallback;

class PxDispatcher
{
public:
	PxDispatcher();
	~PxDispatcher();

public:
	FORCEINLINE PxDefaultCpuDispatcher* GetCpuDispatcher() { return m_pCpuDispatcher; }
	FORCEINLINE ContactCallback*		GetSimulationCallback() { return m_pCallback; }

public:
	void					CreateCpuDispatcher();

private:
	PxDefaultCpuDispatcher* m_pCpuDispatcher;
	ContactCallback*		m_pCallback;
};
