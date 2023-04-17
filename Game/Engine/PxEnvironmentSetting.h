#pragma once
class PxEnvironmentSetting
{
public:
	PxEnvironmentSetting();
	~PxEnvironmentSetting();

public:
	FORCEINLINE PxFoundation* GetFoundation() { return m_pFoundation; }
	FORCEINLINE PxPhysics* GetPhysics() { return m_pPhysics; }
	FORCEINLINE PxDefaultAllocator& GetAllocator() { return m_allocCallback; }
	FORCEINLINE PxDefaultErrorCallback& GetErrorCallback() { return m_errorCallback; }

public:
	void					CreateFoundation();
	void					CreatePhysics(PxPvd* pPvd);

private:
	PxDefaultAllocator		m_allocCallback;
	PxDefaultErrorCallback  m_errorCallback;
	PxFoundation* m_pFoundation;
	PxPhysics* m_pPhysics;
};