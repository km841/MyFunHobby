#include "pch.h"
#include "VeteranHero.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"

VeteranHero::VeteranHero()
	: m_bLandingFlag(false)
	, m_bLandingChecked(false)
	, m_bGroundFlag(false)
{
	SetMonsterState(MONSTER_STATE::PATROL);
}

VeteranHero::~VeteranHero()
{
}

void VeteranHero::Awake()
{
	GameObject::Awake();
}

void VeteranHero::Start()
{
	GameObject::Start();
}

void VeteranHero::Update()
{
	GameObject::Update();

	if (m_bLandingFlag)
	{
		if (MONSTER_STATE::LANDING_READY == MONSTER_STATE::LANDING_READY && !m_bLandingChecked)
		{
			GetRigidBody()->SetVelocity(Vec3::Zero);
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetLinearMaxVelocityForDynamic(2000.f);
			m_bLandingChecked = true;
			SetMonsterState(MONSTER_STATE::LANDING);
			GetAnimator()->Play(L"VeteranHero_Landing", false);
		}
	}

}

void VeteranHero::LateUpdate()
{
	GameObject::LateUpdate();
}

void VeteranHero::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void VeteranHero::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bLandingFlag = true;
		m_bGroundFlag = true;
	}
}

void VeteranHero::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bGroundFlag = false;
	}
}
