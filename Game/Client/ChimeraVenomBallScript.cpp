#include "pch.h"
#include "ChimeraVenomBallScript.h"
#include "Chimera.h"
#include "Clock.h"

ChimeraVenomBallScript::ChimeraVenomBallScript()
	: m_iVenomBallCount(0)
	, m_tDuration(0.8f)
{
}

ChimeraVenomBallScript::~ChimeraVenomBallScript()
{
}

void ChimeraVenomBallScript::LateUpdate()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(GetGameObject());

	if (MONSTER_STATE::SKILL1 == pChimera.lock()->GetMonsterState())
	{
		// Timer 걸어두고 타이머가 끝날 때 애니메이션 클리어
		if (!m_tDuration.IsRunning())
			m_tDuration.Start();
		else
		{
			m_tDuration.Update(WORLD_DELTA_TIME);

			if (m_tDuration.IsFinished())
			{
				if (m_iVenomBallCount < 4)
				{
					// Create Venom Ball!	
					m_iVenomBallCount++;
					m_tDuration.Reset();
					pChimera.lock()->ClearAnimation();
				}

				else
				{
					m_iVenomBallCount = 0;
					m_tDuration.Reset();
					pChimera.lock()->ClearAnimation();
					pChimera.lock()->SetMonsterState(MONSTER_STATE::SKILL1_END);
				}
			}
		}
		

		
	}
	else
	{
		m_iVenomBallCount = 0;
	}
}
