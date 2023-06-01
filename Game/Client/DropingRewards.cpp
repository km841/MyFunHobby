#include "pch.h"
#include "DropingRewards.h"
#include "Clock.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectReturnToPoolEvent.h"
#include "EventManager.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Player.h"

POOL_INIT(DropingRewards);
DropingRewards::DropingRewards()
	: GameObject(LAYER_TYPE::DROPING_REWARDS)
	, m_bDestroy(false)
	, m_tDuration(1.f)
	, m_eDropingRewardKind(DROPING_REWARD_KIND::END)
{
}

DropingRewards::~DropingRewards()
{
}

void DropingRewards::Awake()
{
	GameObject::Awake();
}

void DropingRewards::Start()
{
	GameObject::Start();
}

void DropingRewards::Update()
{
	GameObject::Update();

	if (m_tDuration.IsRunning())
	{
		m_tDuration.Update(DELTA_TIME);

		if (m_tDuration.IsFinished())
		{
			if (!m_bDestroy)
			{
				GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
				GetRigidBody()->SetRotationZForDynamic(0.f);
				GetRigidBody()->SetAngularDamping(PX_MAX_F32);
				GetRigidBody()->SetLinearDamping(PX_MAX_F32);
				GetAnimator()->Play(L"Rewards_Get", false);
				m_bDestroy = true;
			}

			else
			{
				if (GetAnimator()->GetActiveAnimation()->IsFinished())
				{
					m_bDestroy = false;
					m_tDuration.Reset();

					weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
					switch (m_eDropingRewardKind)
					{
					case DROPING_REWARD_KIND::GOLD:
						pPlayer.lock()->GetClobber()->iGold += RANDOM(1, 10);
						break;
					case DROPING_REWARD_KIND::DARK_QUARTZ:
						pPlayer.lock()->GetClobber()->iDarkQuartz += 1;
						break;
					}

					SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
					GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
				}
			}
		}
	}
}

void DropingRewards::LateUpdate()
{
	GameObject::LateUpdate();
}

void DropingRewards::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void DropingRewards::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		if (!m_tDuration.IsRunning())
			m_tDuration.Start();
	}
}

void DropingRewards::OnCollisionExit(shared_ptr<GameObject> pGameObject)
{
}
