#include "pch.h"
#include "AfterImageDrawScript.h"
#include "Player.h"
#include "Timer.h"
#include "AfterImage.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"
#include "Transform.h"
#include "Resources.h"

AfterImageDrawScript::AfterImageDrawScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
	, m_tcDuration(0.3f)
	, m_bTrigger(false)
{
}

AfterImageDrawScript::~AfterImageDrawScript()
{
}

void AfterImageDrawScript::LateUpdate()
{
	shared_ptr<AfterImage> pAfterImage = static_pointer_cast<AfterImage>(GetGameObject());

	if (m_bTrigger != pAfterImage->IsEnable())
	{
		m_tcDuration.Start();
		m_bTrigger = true;
	}

	if (pAfterImage->IsEnable())
	{
		m_tcDuration.Update(DELTA_TIME);

		const FrameData& currFrameData = pAfterImage->GetFrameData();
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(currFrameData.szTexPath, currFrameData.szTexPath);
		assert(pTexture);

		DIRECTION eDirection = pAfterImage->GetDirection();
		Vec3 vSpriteSize = pTexture->GetTexSize();
		Vec2 vLTPos = Vec2(currFrameData.vLTPos.x / vSpriteSize.x, currFrameData.vLTPos.y / vSpriteSize.y);
		Vec2 vSize = Vec2(currFrameData.vSize.x / vSpriteSize.x, currFrameData.vSize.y / vSpriteSize.y);
		Vec2 vOffset = Vec2(currFrameData.vOffset.x / vSpriteSize.x, currFrameData.vOffset.y / vSpriteSize.y);
		Vec2 vAtlasSize = Vec2(100.f / vSpriteSize.x, 100.f / vSpriteSize.y);
		float fProgress = m_tcDuration.GetProgress();
		
		GetMeshRenderer()->GetMaterial()->SetInt(0, 1);
		GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<uint8>(eDirection));
		GetMeshRenderer()->GetMaterial()->SetVec2(0, vLTPos);
		GetMeshRenderer()->GetMaterial()->SetVec2(1, vSize);
		GetMeshRenderer()->GetMaterial()->SetVec2(2, vAtlasSize);
		GetMeshRenderer()->GetMaterial()->SetVec2(3, vOffset);
		GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		GetMeshRenderer()->GetMaterial()->SetFloat(0, 1.f - fProgress);

		if (m_tcDuration.IsFinished())
		{
			pAfterImage->Disable();
			m_tcDuration.Stop();
			m_bTrigger = false;
		}
	}
}
