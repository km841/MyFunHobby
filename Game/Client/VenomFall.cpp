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

VenomFall::VenomFall()
	: GameObject(LAYER_TYPE::UNKNOWN)
	, m_bFinishedIntroFlag(false)
	, m_bFinishedOutroFlag(false)
	, m_tLoopDuration(2.f)
	, m_tSplashTick(0.25f)
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
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			m_bFinishedIntroFlag = true;
			GetAnimator()->Play(L"VenomFall_Loop");

			// Timer On!
			m_tLoopDuration.Start();
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
			}

			if (!m_tSplashTick.IsRunning())
			{
				m_tSplashTick.Start();
			}
			else
			{
				m_tSplashTick.Update(WORLD_DELTA_TIME);
				if (m_tSplashTick.IsFinished())
				{
					CreateVenomSplashAndAddedToScene();
					m_tSplashTick.Reset();
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
		GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VenomSplash>(L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(30.f, 30.f, 30.f), MassProperties());

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
	vPos.y += 300.f;
	pProjectile->GetTransform()->SetLocalPosition(vPos);
	pProjectile->GetTransform()->SetLocalScale(Vec3(30.f, 30.f, 30.f));

	//pProjectile->GetAnimator()->Play(L"VenomSplash_Intro", false);

	pProjectile->Awake();
	pProjectile->GetRigidBody()->SetLinearVelocityForDynamic(PxVec3(0.f, -1.f, 0.f) * 1000.f);
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}
