#include "pch.h"
#include "Animation.h"
#include "Timer.h"
#include "Animator.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Texture.h"

Animation::Animation(const std::vector<FrameData> vFrameDataList)
	: Object(OBJECT_TYPE::ANIMATION)
	, m_bLoop(false)
	, m_iCurFrame(0)
	, m_vFrameDataList(vFrameDataList)
	, m_fAccTime(0.f)
	, m_bFinished(false)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	PushData();

	if (m_bFinished)
		return;

	m_fAccTime += DELTA_TIME;
	if (m_vFrameDataList[m_iCurFrame].fDuration < m_fAccTime)
	{
		m_fAccTime = 0.f;
		m_iCurFrame++;

		if (m_iCurFrame >= m_vFrameDataList[0].iFrameCount)
		{
			if (m_bLoop)
			{
				m_iCurFrame = 0;
			}
			else
			{
				m_bFinished = true;
			}
		}
	}
	
}

void Animation::PushData()
{
	FrameData currFrameData = m_vFrameDataList[m_iCurFrame];
	Vec3 vSpriteSize = m_pTexture->GetTexSize();

	Vec2 vLTPos = Vec2(currFrameData.vLTPos.x / vSpriteSize.x, currFrameData.vLTPos.y / vSpriteSize.y);
	Vec2 vSize = Vec2(currFrameData.vSize.x / vSpriteSize.x, currFrameData.vSize.y / vSpriteSize.y);
	Vec2 vOffset = Vec2(currFrameData.vOffset.x / vSpriteSize.x, currFrameData.vOffset.y / vSpriteSize.y);
	Vec2 vAtlasSize = Vec2(100.f / vSpriteSize.x, 100.f / vSpriteSize.y);

	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetVec2(0, vLTPos);
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetVec2(1, vSize);
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetVec2(2, vAtlasSize);
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetVec2(3, vOffset);
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetTexture(0, m_pTexture);
}

void Animation::RefreshAnimation(const std::vector<FrameData> vFrameDataList)
{
	m_vFrameDataList = vFrameDataList;
	m_iCurFrame = 0;
	m_bFinished = false;
}

void Animation::Load(const wstring& szPath)
{
}

void Animation::Save(const wstring& szPath)
{
}
