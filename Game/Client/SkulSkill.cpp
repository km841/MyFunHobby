#include "pch.h"
#include "SkulSkill.h"

SkulSkill::SkulSkill(float fCooldown, float fDuration)
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_eSkillIndex(SKILL_INDEX::END)
	, m_tCooldown(fCooldown)
	, m_tDuration(fDuration)
{
}
