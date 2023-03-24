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
	if (m_pActiveAnimation)
		m_pActiveAnimation->Update();
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

void Animator::Play(const wstring& szName, bool bLoop, uint32 iSection)
{
	shared_ptr<Animation> pAnimation = FindAnimation(szName);
	assert(pAnimation);

	m_pActiveAnimation = pAnimation;
	m_pActiveAnimation->m_bLoop = bLoop;
	m_pActiveAnimation->m_iSection = iSection;
}

void Animator::AddAnimation(const wstring& szName, shared_ptr<Animation> pAnimation)
{
	assert(pAnimation);
	assert(nullptr == FindAnimation(szName));
	pAnimation->SetAnimator(shared_from_this());
	m_mAnimations[szName] = pAnimation;
}

shared_ptr<Animation> Animator::FindAnimation(const wstring& szName)
{
	auto iter = m_mAnimations.find(szName);

	if (m_mAnimations.end() != iter)
		return iter->second;

	return nullptr;
}
