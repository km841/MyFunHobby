#include "pch.h"
#include "AbyssOrb.h"
#include "Clock.h"
#include "Animator.h"
#include "Animation.h"
#include "EventManager.h"
#include "ObjectRemoveToSceneEvent.h"
#include "Scenes.h"
#include "Scene.h"
#include "RigidBody.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "DecoObject.h"
#include "Light.h"
#include "ObjectAddedToSceneEvent.h"

AbyssOrb::AbyssOrb()
	: m_tLifeTimer(5.f)
	, m_bCompleted(false)
	, m_bDespawn(false)
	, m_tDamageTick(0.3f)
{
}

AbyssOrb::~AbyssOrb()
{
}

void AbyssOrb::Awake()
{
	PlayerProjectile::Awake();
}

void AbyssOrb::Start()
{
	PlayerProjectile::Awake();
}

void AbyssOrb::Update()
{
	PlayerProjectile::Update();


	if (!m_tLifeTimer.IsRunning())
		m_tLifeTimer.Start();

	if (m_tLifeTimer.IsRunning())
	{
		m_tLifeTimer.Update(DELTA_TIME);
		if (m_tLifeTimer.IsFinished())
		{
			if (!m_bCompleted)
			{
				GetAnimator()->Play(L"AbyssOrb_Completed", false);
				m_bCompleted = true;
			}
			
			else
			{
				if (GetAnimator()->GetActiveAnimation()->IsFinished())
				{
					if (!m_bDespawn)
					{
						GetAnimator()->Play(L"AbyssOrb_Despawn", false);
						m_bDespawn = true;
						GetRigidBody()->SetVelocity(Vec3::Zero);

						Vec3 vExtendVolume = GetTransform()->GetLocalScale();
						vExtendVolume.x += 200.f;
						vExtendVolume.y += 200.f;

						GET_SINGLE(CollisionManager)->SetForceInLayer(
							LAYER_TYPE::PARTICLE,
							GetTransform()->GetPhysicalPosition(),
							vExtendVolume,
							Vec3(0.f, 1000.f, 0.f));
					}

					else
					{
						if (GetAnimator()->GetActiveAnimation()->IsFinished())
						{
							Disable();
							SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
							GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));

						}
					}
				}
			}


		}

		else
		{
			if (!m_tDamageTick.IsRunning())
				m_tDamageTick.Start();

			m_tDamageTick.Update(DELTA_TIME);

			if (m_tDamageTick.IsFinished())
			{
				GET_SINGLE(CollisionManager)->SetForceInLayer(
					LAYER_TYPE::PARTICLE,
					GetTransform()->GetPhysicalPosition(),
					GetTransform()->GetLocalScale(),
					Vec3(static_cast<float>(RANDOM(0, 1) ? -50 : 50), 100.f, 0.f));

				m_tDamageTick.Reset();
			}
		}
	}


	
}

void AbyssOrb::LateUpdate()
{
	PlayerProjectile::LateUpdate();
}

void AbyssOrb::FinalUpdate()
{
	PlayerProjectile::FinalUpdate();
}

