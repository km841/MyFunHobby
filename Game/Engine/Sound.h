#pragma once
#include "Object.h"
class Sound :
	public Object
{
public:
	Sound();
	virtual ~Sound();

	virtual void Load(const std::wstring& szPath) override;

	void Play();
	void Stop();
	void Set3DAttributes(const Vec3& vPos, const Vec3& vVel);
	void SetLoop(bool loop) { m_bLoop = loop; }
	void SetVolume(float fRatio) { m_pChannel->setVolume(fRatio); }
	

private:
	FMOD::Sound* m_pSound;
	FMOD::Channel* m_pChannel;
	float m_fMinDistance;
	float m_fMaxDistance;
	bool m_bLoop;
};