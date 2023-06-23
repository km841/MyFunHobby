#include "pch.h"
#include "VenomBallProjectile.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectRemoveToSceneEvent.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "Tile.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "ComponentObject.h"
#include "SoundSource.h"
#include "Resources.h"

VenomBallProjectile::VenomBallProjectile()
	: m_bChecked(false)
	, m_bDespawnFlag(false)
{
}

VenomBallProjectile::~VenomBallProjectile()
{
}

void VenomBallProjectile::Awake()
{
	MonsterProjectile::Awake();
}

void VenomBallProjectile::Start()
{
	MonsterProjectile::Start();
}

void VenomBallProjectile::Update()
{
	MonsterProjectile::Update();

	if (m_bDespawnFlag)
	{
		GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
		GetRigidBody()->SetRotationZForDynamic(0.f);
		GetRigidBody()->SetAngularDamping(PX_MAX_F32);
		GetRigidBody()->SetLinearDamping(PX_MAX_F32);
		GetAnimator()->Play(L"VenomBall_Despawn", false);

		shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Chimera_VenomCannon_Despawn", L"..\\Resources\\Sound\\Chimera_VenomCannon_Despawn.wav");
		SCENE_SOUND->SetClip(pSound);
		SCENE_SOUND->Play();

		Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
		Vec3 vMySize = GetTransform()->GetLocalPosition();
		GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vMyPos, Vec3(200.f, 200.f, 0.f), Vec3::Zero, 3.f);
		m_bDespawnFlag = false;
	}

	if (GetAnimator()->GetActiveAnimation() && GetAnimator()->GetActiveAnimation()->IsFinished())
	{
		m_bChecked = false;
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
	}

}

void VenomBallProjectile::LateUpdate()
{
	MonsterProjectile::LateUpdate();
}

void VenomBallProjectile::FinalUpdate()
{
	MonsterProjectile::FinalUpdate();
}

void VenomBallProjectile::OnCollisionEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::TILE == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}

	}
}

void VenomBallProjectile::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
	if (LAYER_TYPE::PLAYER == pGameObject->GetLayerType())
	{
		// Despawn!
		if (!m_bChecked)
		{
			m_bDespawnFlag = true;
			m_bChecked = true;
		}
	}
}

void VenomBallProjectile::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}
