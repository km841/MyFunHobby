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

	// 1. Ʈ���Ÿ� ���ش�
	// 2. Ÿ�̸Ӹ� �Ѱ� Ʈ���� Off
	// 3. Ʈ���Ű� ���� ���� Enable�Ǿ��ٴ� �ǹ��̹Ƿ�, Ÿ�̸Ӱ� ����
	// 4. Ÿ�̸��� Progress�� ���� ��� ���ۿ� 0~1�� �� ����
	// 5. 0~1�� ������ ������ ����������, 0�� �Ǹ� Disable�ȴ�.

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
