#pragma once
class Clock
{
	DECLARE_SINGLE(Clock);

public:
	void   Init();
	void   Update();

	FORCEINLINE uint32 GetFPS()       const { return m_iFPS; }
	FORCEINLINE float  GetWorldDeltaTime() const { return m_fWorldDeltaTime; }
	FORCEINLINE float  GetObjectDeltaTime() const { return m_fObjectDeltaTime; }
	FORCEINLINE void   Pause()				{ m_bPause = true; }
	FORCEINLINE void   Play()				{ m_bPause = false; }

	bool  IsPause() { return m_bPause; }


private:
	uint32 m_iFPS;

	uint64 m_iFrequency;
	uint64 m_iPrevCount;

	uint32 m_iFrameCount;

	float  m_fFrameTime;
	float  m_fObjectDeltaTime;
	float  m_fWorldDeltaTime;


	bool m_bPause = false;

};

