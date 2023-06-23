#include "pch.h"
#include "VenomFall.h"
#include "Animation.h"
#include "Animator.h"
#include "Clock.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "VenomSplash.h"
#include "ObjectFactory.h"
#include "ObjectAddedToSceneEvent.h"
#include "RigidBody.h"
#include "DebugRenderer.h"
#include "ComponentObject.h"
#include "SoundSource.h"

VenomFall::VenomFall()
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_bFinishedIntroFlag(false)
	, m_bFinishedOutroFlag(false)
	, m_bCreatedSplashFlag(false)
	, m_tLoopDuration(2.f)
{
}

VenomFall::~VenomFall()
{
}

void VenomFall::Awake()
{
	GameObject::Awake();
}

void VenomFall::Start()
{
	GameObject::Start();
}

void VenomFall::Update()
{
	GameObject::Update();

	if (!m_bFinishedIntroFlag)
	{
		if (!m_bCreatedSplashFlag)
		{
			CreateVenomSplashAndAddedToScene();
			m_bCreatedSplashFlag = true;

			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Chimera_VenomFall_Intro", L"..\\Resources\\Sound\\Chimera_VenomFall_Intro.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
		}

		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			
			m_bFinishedIntroFlag = true;
			GetAnimator()->Play(L"VenomFall_Loop");

			// Timer On!
			m_tLoopDuration.Start();

			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Chimera_VenomFall_Loop", L"..\\Resources\\Sound\\Chimera_VenomFall_Loop.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->SetLoop(true);
			SCENE_SOUND->Play();
		}
	}
	else
	{
		m_tLoopDuration.Update(WORLD_DELTA_TIME);

		if (m_tLoopDuration.IsFinished())
		{
			if (!m_bFinishedOutroFlag)
			{
				GetAnimator()->Play(L"VenomFall_Outro", false);
				m_bFinishedOutroFlag = true;

				// Loop Sound
				{
					shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Chimera_VenomFall_Loop", L"..\\Resources\\Sound\\Chimera_VenomFall_Loop.wav");
					SCENE_SOUND->SetClip(pSound);
					SCENE_SOUND->SetLoop(false);
					SCENE_SOUND->Stop();
				}

				// Outro Sound
				{
					shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Chimera_VenomFall_Loop_To_End", L"..\\Resources\\Sound\\Chimera_VenomFall_Loop_To_End.wav");
					SCENE_SOUND->SetClip(pSound);
					SCENE_SOUND->Play();
				}
			}
		}

		if (m_bFinishedOutroFlag)
		{
			if (GetAnimator()->GetActiveAnimation()->IsFinished())
			{
				SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
			}
		}
	}
}

void VenomFall::LateUpdate()
{
	GameObject::LateUpdate();
}

void VenomFall::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void VenomFall::CreateVenomSplashAndAddedToScene()
{
	shared_ptr<VenomSplash> pProjectile =
		GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VenomSplash>(L"Forward", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 30.f, 30.f), MassProperties());

	pProjectile->AddComponent(make_shared<Animator>());
	pProjectile->AddComponent(make_shared<DebugRenderer>());

	// Venom Splash Intro
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomSplash_Intro", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_splash_intro.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomSplash_Intro", pAnimation);
	}

	// Venom Splash Loop
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomSplash_Loop", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_splash_loop.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomSplash_Loop", pAnimation);
	}

	// Venom Splash Outro
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VenomSplash_Outro", L"..\\Resources\\Animation\\Chimera\\chimera_venom_fall_splash_outro.anim");
		pProjectile->GetAnimator()->AddAnimation(L"VenomSplash_Outro", pAnimation);
	}

	Vec3 vPos = GetTransform()->GetLocalPosition();
	vPos.y += 900.f;
	vPos.z -= 10.f;
	pProjectile->GetTransform()->SetLocalPosition(vPos);
	pProjectile->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}
