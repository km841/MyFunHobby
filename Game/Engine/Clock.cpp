#include "pch.h"
#include "Clock.h"
#include "Input.h"

void Clock::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_iFrequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_iPrevCount)); // CPU Å¬·°
}

void Clock::Update()
{
	uint64 iCurrentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&iCurrentCount));

	m_fWorldDeltaTime = (iCurrentCount - m_iPrevCount) / static_cast<float>(m_iFrequency);
	m_fObjectDeltaTime = m_fWorldDeltaTime;
	if (m_fWorldDeltaTime > (1.f / 60.f))
		m_fWorldDeltaTime = (1.f / 60.f);

	if (m_bPause)
		m_fObjectDeltaTime = 0.000001f;

	m_iPrevCount = iCurrentCount;

	m_iFrameCount++;
	m_fFrameTime += m_fWorldDeltaTime;

	if (m_fFrameTime > 1.f)
	{
		m_iFPS = static_cast<uint32>(m_iFrameCount / m_fFrameTime);

		m_fFrameTime = 0.f;
		m_iFrameCount = 0;
	}
}
