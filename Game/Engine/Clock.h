#pragma once
class Clock
{
	DECLARE_SINGLE(Clock);

public:
	void   Init();
	void   Update();

	FORCEINLINE uint32 GetFPS()       const { return m_iFPS; }
	FORCEINLINE float  GetDeltaTime() const { return m_fDeltaTime; }

private:
	uint32 m_iFPS;

	uint64 m_iFrequency;
	uint64 m_iPrevCount;

	uint32 m_iFrameCount;

	float  m_fFrameTime;
	float  m_fDeltaTime;

};

