#include "pch.h"
#include "SkulSkill.h"
#include "Clock.h"

SkulSkill::SkulSkill(float fCooldown, float fDuration)
	: m_eSkillIndex(SKILL_INDEX::END)
	, m_tCooldown(fCooldown)
	, m_tDuration(fDuration)
{
}

void SkulSkill::UpdateSkillCooldown()
{
	m_tCooldown.Update(DELTA_TIME);
}


