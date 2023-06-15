#include "pch.h"
#include "VenomSplash.h"
#include "Animator.h"
#include "Animation.h"
#include "Clock.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "RigidBody.h"
#include "Transform.h"

VenomSplash::VenomSplash()
	: GameObject(LAYER_TYPE::MONSTER_PROJECTILE)
	, m_bCollisionFlag(false)
	, m_bChecked(false)
	, m_bIntroFinishedFlag(false)
	, m_bOutroFinishedFlag(false)
	, m_tLoopTimer(2.5f)
{
}

VenomSplash::~VenomSplash()
{
}

void VenomSplash::Awake()
{
	GameObject::Awake();
}

void VenomSplash::Start()
{
	GameObject::Start();
}

void VenomSplash::Update()
{
	GameObject::Update();

	if (m_bCollisionFlag)
	{
		if (!m_bChecked)
		{
			GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
			GetRigidBody()->SetRotationZForDynamic(0.f);
			GetRigidBody()->SetAngularDamping(PX_MAX_F32);
			GetRigidBody()->SetLinearDamping(PX_MAX_F32);
			m_bChecked = true;
			GetAnimator()->Play(L"VenomSplash_Intro", false);
		}

		else
		{
			if (!m_bIntroFinishedFlag && GetAnimator()->GetActiveAnimation()->IsFinished())
			{
				m_bIntroFinishedFlag = true;
				GetAnimator()->Play(L"VenomSplash_Loop");
				m_tLoopTimer.Start();



			}

			if (m_bIntroFinishedFlag)
			{
				m_tLoopTimer.Update(WORLD_DELTA_TIME);

				if (m_tLoopTimer.IsFinished())
				{
					if (!m_bOutroFinishedFlag)
					{
						GetAnimator()->Play(L"VenomSplash_Outro", false);
						m_bOutroFinishedFlag = true;
					}
					else
					{
						if (GetAnimator()->GetActiveAnimation()->IsFinished())
						{
							SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
							GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
						}
					}
				}
			}
		}
	}
}

void VenomSplash::LateUpdate()
{
	GameObject::LateUpdate();
}

void VenomSplash::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void VenomSplash::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bCollisionFlag = true;
	}
}

void VenomSplash::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}

void VenomSplash::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{

	}
}

void VenomSplash::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
