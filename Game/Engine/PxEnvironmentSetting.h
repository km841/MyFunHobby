#pragma once
class PxEnvironmentSetting
{
public:
	PxEnvironmentSetting();
	~PxEnvironmentSetting();

public:
	PxFoundation*			GetFoundation() { return m_pFoundation; }
	PxPhysics*				GetPhysics() { return m_pPhysics; }

	void					CreateFoundation();
	void					CreatePhysics();

	PxDefaultAllocator&		GetAllocator() { return m_allocCallback; }
	PxDefaultErrorCallback& GetErrorCallback() { return m_errorCallback; }

private:
	PxDefaultAllocator		m_allocCallback;
	PxDefaultErrorCallback  m_errorCallback;
	PxFoundation*			m_pFoundation;
	PxPhysics*				m_pPhysics;
};

