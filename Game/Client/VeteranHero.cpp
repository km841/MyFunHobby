#include "pch.h"
#include "VeteranHero.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"

VeteranHero::VeteranHero()
	: m_bLandingFlag(false)
	, m_bLandingChecked(false)
{
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
			GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
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

void VeteranHero::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bLandingFlag = true;
	}
}

void VeteranHero::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}
