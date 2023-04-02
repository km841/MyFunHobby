#include "pch.h"
#include "LittleBone.h"

LittleBone::LittleBone()
	: Skul(SKUL_GRADE::NORMAL)
	, m_eLittleBoneState(LITTLE_BONE_STATE::HAS_HEAD)
{
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
}

void LittleBone::Awake()
{
	Skul::Awake();
}

void LittleBone::Start()
{
	Skul::Start();
}

void LittleBone::Update()
{
	Skul::Update();
}

void LittleBone::LateUpdate()
{
	Skul::LateUpdate();
}

void LittleBone::FinalUpdate()
{
	Skul::FinalUpdate();
}

void LittleBone::LoseHead()
{
	m_eLittleBoneState = LITTLE_BONE_STATE::NO_HEAD;
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
}

void LittleBone::GetHead()
{
	m_eLittleBoneState = LITTLE_BONE_STATE::HAS_HEAD;
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
}
