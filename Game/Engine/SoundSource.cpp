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
	Vec3 vLook = GetTransform()->GetLook();

	m_pSound->Set3DAttributes(vPos, vLook);
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
