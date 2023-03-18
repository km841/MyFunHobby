#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Engine.h"
#include "Resources.h"

Animator::Animator()
	: Component(COMPONENT_TYPE::ANIMATOR)
{
}

Animator::~Animator()
{
}

void Animator::Update()
{
	if (m_pCurAnimation)
		m_pCurAnimation->Update();
}

void Animator::CreateAnimation(const std::vector<FrameData> vFrameDataList)
{
	assert(!vFrameDataList.empty());
	shared_ptr<Animation> pAnimation = make_shared<Animation>(vFrameDataList);

	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(vFrameDataList[0].szTexPath, vFrameDataList[0].szTexPath);
	assert(pTexture);
	pAnimation->SetTexture(pTexture);
	pAnimation->SetName(vFrameDataList[0].szName);
	pAnimation->SetAnimator(shared_from_this());
	m_mAnimations[vFrameDataList[0].szName] = pAnimation;
}

void Animator::Play(const wstring& szAnimName, bool bLoop)
{
	auto iter = m_mAnimations.find(szAnimName);
	assert(m_mAnimations.end() != iter);
	m_pCurAnimation = iter->second;
	m_pCurAnimation->m_bLoop = bLoop;
}
