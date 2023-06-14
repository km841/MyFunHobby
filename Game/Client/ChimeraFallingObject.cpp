#include "pch.h"
#include "ChimeraFallingObject.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectFactory.h"
#include "AnimationLocalEffect.h"

ChimeraFallingObject::ChimeraFallingObject()
	: GameObject(LAYER_TYPE::FALLING_OBJECT)
	, m_bChecked(false)
	, m_bTriggerFlag(false)
	, m_bDestroyed(false)
	, m_bDestroyedChecked(false)
{
}

ChimeraFallingObject::~ChimeraFallingObject()
{
}

void ChimeraFallingObject::Awake()
{
	GameObject::Awake();
}

void ChimeraFallingObject::Start()
{
	GameObject::Start();
}

void ChimeraFallingObject::Update()
{
	GameObject::Update();

	if (m_bTriggerFlag)
	{
		if (!m_bChecked)
		{
			// Create Smoke Effect!
			CreateSmokeEffectAndAddedToScene();
			GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
			GetRigidBody()->SetRotationZForDynamic(0.f);
			GetRigidBody()->SetAngularDamping(PX_MAX_F32);
			GetRigidBody()->SetLinearDamping(PX_MAX_F32);
			m_bChecked = true;
		}
		else
		{
			GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		}
	}

	if (m_bDestroyed)
	{
		if (!m_bDestroyedChecked)
		{
			// Destroy Smoke
			CreateDestroySmokeAndAddedToScene();
			m_bDestroyedChecked = true;
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
		}
	}
}

void ChimeraFallingObject::LateUpdate()
{
	GameObject::LateUpdate();
}

void ChimeraFallingObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void ChimeraFallingObject::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		m_bTriggerFlag = true;
	}
}

void ChimeraFallingObject::CreateSmokeEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pEffect =
		GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<AnimationLocalEffect>(L"Forward");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.z -= 0.5f;
	pEffect->GetTransform()->SetLocalPosition(vPos);

	pEffect->AddComponent(make_shared<Animator>());

	// Landing Smoke
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"LandingSmoke", L"..\\Resources\\Animation\\Chimera\\falling_object_landing_smoke.anim");
		pEffect->GetAnimator()->AddAnimation(L"LandingSmoke", pAnimation);
	}

	pEffect->GetAnimator()->Play(L"LandingSmoke", false);
	pEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pEffect, eSceneType));

}

void ChimeraFallingObject::CreateDestroySmokeAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pEffect =
		GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<AnimationLocalEffect>(L"Forward");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.z -= 0.5f;
	pEffect->GetTransform()->SetLocalPosition(vPos);

	pEffect->AddComponent(make_shared<Animator>());

	// Destroy Smoke
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DestroySmoke", L"..\\Resources\\Animation\\Chimera\\falling_object_destroy_smoke.anim");
		pEffect->GetAnimator()->AddAnimation(L"DestroySmoke", pAnimation);
	}

	pEffect->GetAnimator()->Play(L"DestroySmoke", false);
	pEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pEffect, eSceneType));
}
