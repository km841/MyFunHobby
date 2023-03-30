#include "pch.h"
#include "AfterImageDrawScript.h"
#include "Player.h"
#include "Timer.h"
#include "AfterImage.h"
#include "MeshRenderer.h"
#include "Material.h"

AfterImageDrawScript::AfterImageDrawScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
	, m_tcDuration(0.5f)
{
	m_tcDuration.Disable();
}

AfterImageDrawScript::~AfterImageDrawScript()
{
}

void AfterImageDrawScript::LateUpdate()
{
	shared_ptr<AfterImage> pAfterImage = static_pointer_cast<AfterImage>(GetGameObject());

	if (pAfterImage->IsTrigger())
	{
		m_tcDuration.Start();
		pAfterImage->Check();
	}

	// 1. 트리거를 켜준다
	// 2. 타이머를 켜고 트리거 Off
	// 3. 트리거가 켜진 것은 Enable되었다는 의미이므로, 타이머가 돈다
	// 4. 타이머의 Progress에 따라 상수 버퍼에 0~1의 값 전달
	// 5. 0~1의 값으로 서서히 투명해지며, 0이 되면 Disable된다.

	if (GetGameObject()->IsEnable())
	{
		m_tcDuration.Update(DELTA_TIME);

		float fProgress = m_tcDuration.GetProgress();
		GetMeshRenderer()->GetMaterial()->SetFloat(0, fProgress);
		if (m_tcDuration.IsFinished())
		{
			m_tcDuration.Stop();
			m_tcDuration.Disable();
			GetGameObject()->Disable();
		}
	}
}
