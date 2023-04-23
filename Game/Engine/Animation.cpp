#include "pch.h"
#include "Animation.h"
#include "Clock.h"
#include "Animator.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "Resources.h"
#include "Transform.h"

Animation::Animation()
	: Object(OBJECT_TYPE::ANIMATION)
	, m_bLoop(false)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinished(false)
	, m_iSection(0)
	, m_bHitChecked(false)
	, m_iHitFrame(-1)
{
}

Animation::Animation(const std::vector<FrameData> vFrameDataList)
	: Object(OBJECT_TYPE::ANIMATION)
	, m_bLoop(false)
	, m_iCurFrame(0)
	, m_vFrameDataList(vFrameDataList)
	, m_fAccTime(0.f)
	, m_bFinished(false)
	, m_iSection(0)
	, m_bHitChecked(false)
	, m_iHitFrame(-1)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_bFinished)
		return;

	ImVec2 vSize = m_vFrameDataList[m_iCurFrame].vSize;
	m_pAnimator.lock()->GetTransform()->SetLocalScale(Vec3(vSize.x, vSize.y, 1.f));

	PushData();

	m_fAccTime += DELTA_TIME;
	if (m_vFrameDataList[m_iCurFrame].fDuration < m_fAccTime)
	{
		m_fAccTime = 0.f;

		if (1 == m_vFrameDataList[0].iFrameCount)
			return;

		m_iCurFrame++;

		if (m_iCurFrame >= m_vFrameDataList[0].iFrameCount)
		{
			if (m_bLoop)
			{
				if (0 > m_iSection)
					m_iCurFrame = m_vFrameDataList[0].iFrameCount + m_iSection;
				else
					m_iCurFrame = m_iSection;
				m_bHitChecked = false;
			
			}
			else
			{
				m_bFinished = true;
			}
		}
	}
	
}

void Animation::SetTriggerFrame(int32 iTriggerFrame)
{
	if (m_vTriggerFrames.empty())
		m_vTriggerFrames.resize(m_vFrameDataList[0].iFrameCount, false);
	if (m_vTriggerChecked.empty())
		m_vTriggerChecked.resize(m_vFrameDataList[0].iFrameCount, false);

	assert(m_iCurFrame < m_vTriggerChecked.size());
	m_vTriggerFrames[iTriggerFrame] = true;
}

void Animation::CheckToTriggerFrame()
{
	assert(m_iCurFrame < m_vTriggerChecked.size());
	m_vTriggerChecked[m_iCurFrame] = true;
}

bool Animation::IsTriggerFrame()
{
	assert(m_iCurFrame < m_vTriggerChecked.size());
	return m_vTriggerFrames[m_iCurFrame] && !m_vTriggerChecked[m_iCurFrame];
}

void Animation::SetHitFrame(int32 iHitFrame)
{
	assert(iHitFrame < m_vFrameDataList[0].iFrameCount);
	m_iHitFrame = iHitFrame;
}

float Animation::GetAnimationProgress()
{
	assert(!m_vFrameDataList.empty());
	assert(0 != m_vFrameDataList[0].iFrameCount);

	return m_iCurFrame / static_cast<float>(m_vFrameDataList[0].iFrameCount);
}

void Animation::Reset()
{
	m_iCurFrame = 0;
	m_bFinished = false;
	m_bHitChecked = false;

	if (!m_vTriggerChecked.empty())
	{
		for (int32 i = 0; i < m_vTriggerChecked.size(); ++i)
			m_vTriggerChecked[i] = false;
	}
}

void Animation::PushData()
{
	DIRECTION eDirection = m_pAnimator.lock()->GetGameObject()->GetDirection();
	FrameData currFrameData = m_vFrameDataList[m_iCurFrame];

	Vec3 vSpriteSize = m_pTexture->GetTexSize();
	Vec2 vLTPos = Vec2(currFrameData.vLTPos.x / vSpriteSize.x, currFrameData.vLTPos.y / vSpriteSize.y);
	Vec2 vSize = Vec2(currFrameData.vSize.x / vSpriteSize.x, currFrameData.vSize.y / vSpriteSize.y);
	Vec2 vOffset = Vec2(currFrameData.vOffset.x / vSpriteSize.x, currFrameData.vOffset.y  / vSpriteSize.y);
	Vec2 vAtlasSize = Vec2(100.f / vSpriteSize.x, 100.f / vSpriteSize.y);

	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetInt(0, 1);
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<uint8>(eDirection));
	m_pAnimator.lock()->GetMeshRenderer()->GetMaterial()->SetInt(2, m_iCurFrame);
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
	m_bHitChecked = false;
}


void Animation::Load(const wstring& szPath)
{
	std::wifstream ifs(szPath, std::ios::in);

	int32 iCount = 0;
	wstring szTexPath, szName;

	ifs >> iCount;
	ifs.ignore(1);

	assert(iCount != 0);

	getline(ifs, szName);
	getline(ifs, szTexPath);

	m_vFrameDataList.resize(iCount);

	for (int32 i = 0; i < iCount; ++i)
	{
		ifs >> m_vFrameDataList[i].vLTPos.x >> m_vFrameDataList[i].vLTPos.y;
		ifs.ignore(1);
		ifs >> m_vFrameDataList[i].vSize.x >> m_vFrameDataList[i].vSize.y;
		ifs.ignore(1);
		ifs >> m_vFrameDataList[i].vOffset.x >> m_vFrameDataList[i].vOffset.y;
		ifs.ignore(1);
		ifs >> m_vFrameDataList[i].fDuration;
		ifs.ignore(1);

		m_vFrameDataList[i].szName = szName;
		m_vFrameDataList[i].szTexPath = szTexPath;
		m_vFrameDataList[i].iFrameCount = iCount;
	}

	m_pTexture = GET_SINGLE(Resources)->Load<Texture>(szTexPath, szTexPath);
	assert(m_pTexture);

	ifs.close();
}

void Animation::Save(const wstring& szPath)
{
}
