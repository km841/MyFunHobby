#pragma once
class Timer
{
	DECLARE_SINGLE(Timer);

public:
	void   Init();
	void   Update();

	uint32 GetFPS() { return m_iFPS; }
	float  GetDeltaTime() { return m_fDeltaTime; }

private:
	uint32 m_iFPS;

	uint64 m_iFrequency;
	uint64 m_iPrevCount;

	uint32 m_iFrameCount;

	float  m_fFrameTime;
	float  m_fDeltaTime;

};

