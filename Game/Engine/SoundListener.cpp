#include "pch.h"
#include "SoundListener.h"
#include "Transform.h"
#include "Sounds.h"

SoundListener::SoundListener()
	: Component(COMPONENT_TYPE::SOUND_LISTENER)
{
}

SoundListener::~SoundListener()
{
}

void SoundListener::Awake()
{
}

void SoundListener::Start()
{
}

void SoundListener::Update()
{
}

void SoundListener::LateUpdate()
{
	Vec3 vPos = GetTransform()->GetLocalPosition();
	if (GetPhysical())
		vPos = GetTransform()->GetPhysicalPosition();

	Vec3 vLook= GetTransform()->GetLook();
	Vec3 vUp = GetTransform()->GetUp();

	Vec3 vVel = { 0.0f, 0.0f, 0.0f };
	GET_SINGLE(Sounds)->Set3DListenerAttributes(&vPos, &vVel, &vLook, &vUp);
}

void SoundListener::FinalUpdate()
{
}
