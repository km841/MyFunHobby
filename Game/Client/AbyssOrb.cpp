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
#include "ComponentObject.h"
#include "SoundSource.h"
#include "Resources.h"

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
	CreateLightAndAddedToScene();
}

void AbyssOrb::Start()
{
	PlayerProjectile::Awake();

	shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"HighWarlock_Orb_completed_Roof", L"..\\Resources\\Sound\\HighWarlock_Orb_completed_Roof.wav");
	SCENE_SOUND->SetClip(pSound);
	SCENE_SOUND->SetLoop(true);
	SCENE_SOUND->Play();
}

void AbyssOrb::Update()
{
	PlayerProjectile::Update();


	if (!m_tLifeTimer.IsRunning())
		m_tLifeTimer.Start();

	if (m_tLifeTimer.IsRunning())
	{
		m_tLifeTimer.Update(OBJECT_DELTA_TIME);
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
						shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"HighWarlock_Orb_Explosion_completed", L"..\\Resources\\Sound\\HighWarlock_Orb_Explosion_completed.wav");
						SCENE_SOUND->SetClip(pSound);
						SCENE_SOUND->SetLoop(false);
						SCENE_SOUND->Play();

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

						GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
							GetTransform()->GetPhysicalPosition(),
							GetTransform()->GetLocalScale() * 2.f,
							Vec3(0.f, 500.f, 0.f),
							static_cast<float>(RANDOM(30, 50)), DAMAGE_TYPE::FROM_PLAYER_MAGIC, L"..\\Resources\\Sound\\Hit_Blunt_Large.wav");
					}

					else
					{
						if (GetAnimator()->GetActiveAnimation()->IsFinished())
						{
							Disable();
							SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
							GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pLight, eSceneType));
							GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
							
							// Roof Sound Off
							{
								shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"HighWarlock_Orb_completed_Roof", L"..\\Resources\\Sound\\HighWarlock_Orb_completed_Roof.wav");
								SCENE_SOUND->SetClip(pSound);
								SCENE_SOUND->SetLoop(false);
								SCENE_SOUND->Stop();
							}


							// Explosion Sound On
							{

							}

						}
					}
				}
			}


		}

		else
		{
			if (!m_tDamageTick.IsRunning())
				m_tDamageTick.Start();

			m_tDamageTick.Update(OBJECT_DELTA_TIME);

			if (m_tDamageTick.IsFinished())
			{
				GET_SINGLE(CollisionManager)->SetForceInLayer(
					LAYER_TYPE::PARTICLE,
					GetTransform()->GetPhysicalPosition(),
					GetTransform()->GetLocalScale(),
					Vec3(static_cast<float>(RANDOM(0, 1) ? -50 : 50), 100.f, 0.f));

				GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(
					GetTransform()->GetPhysicalPosition(),
					GetTransform()->GetLocalScale() * 2.f,
					Vec3(0.f, 0.f, 0.f),
					static_cast<float>(RANDOM(3, 10)), DAMAGE_TYPE::FROM_PLAYER_MAGIC, L"..\\Resources\\Sound\\Hit_Blunt_Large.wav");

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

void AbyssOrb::CreateLightAndAddedToScene()
{
	m_pLight = make_shared<GameObject>(LAYER_TYPE::UNKNOWN);
	m_pLight->AddComponent(make_shared<Transform>());
	m_pLight->GetTransform()->SetParent(GetTransform());
	m_pLight->AddComponent(make_shared<Light>());
	m_pLight->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
	m_pLight->GetLight()->SetLightRange(600.f);
	m_pLight->GetLight()->SetDiffuse(Vec3(0.2f, 1.f, 0.2f));

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pLight, eSceneType));
}

