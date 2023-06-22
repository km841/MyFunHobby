#include "pch.h"
#include "Sound.h"
#include "Sounds.h"

Sound::Sound()
	: Object(OBJECT_TYPE::SOUND)
	, m_pSound(nullptr)
	, m_pChannel(nullptr)
	, m_fMinDistance(1.0f)
	, m_fMaxDistance(1000.0f)
	, m_bLoop(false)
{

}

Sound::~Sound()
{
	m_pSound->release();
	m_pSound = nullptr;
}

void Sound::Load(const std::wstring& szPath)
{
	std::string cPath(szPath.begin(), szPath.end());
	bool bResult = GET_SINGLE(Sounds)->CreateSound(cPath, &m_pSound);
	assert(bResult);
	m_pSound->set3DMinMaxDistance(m_fMinDistance, m_fMaxDistance);
}

void Sound::Play()
{
	if (m_bLoop)
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	else
		m_pSound->setMode(FMOD_LOOP_OFF);

	GET_SINGLE(Sounds)->SoundPlay(m_pSound, &m_pChannel);
}

void Sound::Stop()
{
	m_pChannel->stop();
}

void Sound::Set3DAttributes(const Vec3& pos, const Vec3& vel)
{
	FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
	FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

	m_pChannel->set3DAttributes(&fmodPos, &fmodVel);
}

