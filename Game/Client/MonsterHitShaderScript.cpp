#include "pch.h"
#include "MonsterHitShaderScript.h"
#include "Monster.h"
#include "Clock.h"
#include "MeshRenderer.h"
#include "Material.h"

MonsterHitShaderScript::MonsterHitShaderScript()
	: m_fRatio(0.f)
	, m_ePrevState(MONSTER_STATE::IDLE)
{
}

MonsterHitShaderScript::~MonsterHitShaderScript()
{
}

void MonsterHitShaderScript::LateUpdate()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(GetGameObject());
	MONSTER_STATE eCurState = pMonster.lock()->GetMonsterState();
	if (MONSTER_STATE::WEAK_HIT == eCurState/* && eCurState != m_ePrevState*/)
	{
		if (m_fRatio < 0.99f)
			m_fRatio = 1.f;
	}

	if (0.f < m_fRatio)
	{
		m_fRatio -= DELTA_TIME * 10.f;
	}

	m_ePrevState = eCurState;
	GetMeshRenderer()->GetMaterial()->SetFloat(1, m_fRatio);
}
