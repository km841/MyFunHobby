#include "pch.h"
#include "SoundSource.h"
#include "Sound.h"
#include "Transform.h"

SoundSource::SoundSource()
	: Component(COMPONENT_TYPE::SOUND_SOURCE)
{
}

SoundSource::~SoundSource()
{
}

void SoundSource::Awake()
{
}

void SoundSource::Start()
{
}

void SoundSource::Update()
{
}

void SoundSource::LateUpdate()
{
	Vec3 vPos = GetTransform()->GetLocalPosition();
	if (GetPhysical())
		vPos = GetTransform()->GetPhysicalPosition();
	Vec3 vLook = GetTransform()->GetLook();
	if (m_pSound)
		m_pSound->Set3DAttributes(vPos, vLook);

	if (m_pBgmSound)
		m_pBgmSound->Set3DAttributes(vPos, vLook);
}

void SoundSource::FinalUpdate()
{
}

void SoundSource::Play()
{
	m_pSound->Play();
}

void SoundSource::Stop()
{
	m_pSound->Stop();
}

void SoundSource::SetLoop(bool loop)
{
	m_pSound->SetLoop(loop);
}

void SoundSource::SetBGMClip(std::shared_ptr<Sound> clip)
{
	StopBGM();
	m_pBgmSound = clip;
	m_pBgmSound->SetVolume(0.5f);
}

void SoundSource::PlayBGM()
{
	m_pBgmSound->SetLoop(true);
	m_pBgmSound->Play();
}

void SoundSource::StopBGM()
{
	if (m_pBgmSound)
	m_pBgmSound->Stop();
}
