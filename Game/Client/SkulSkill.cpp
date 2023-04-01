#include "pch.h"
#include "SkulSkill.h"

SkulSkill::SkulSkill(float fCooldown)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkillPos(SKUL_SKILL_POS::FIRST)
	, m_tCooldown(fCooldown)
{
}
