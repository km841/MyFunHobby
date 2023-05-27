#include "pch.h"
#include "Monster.h"
#include "Transform.h"
#include "Physical.h"
#include "Clock.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"
#include "Animation.h"
#include "Animator.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "AnimationGlobalEffect.h"
#include "Scene.h"
#include "Scenes.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Resources.h"
#include "MonsterHPHUD.h"
#include "ObjectFactory.h"
#include "MonsterHealthBarShowScript.h"
#include "ObjectRemoveToSceneEvent.h"
#include "AnimationLocalEffect.h"
#include "ObjectReturnToPoolEvent.h"
#include "ParticleSystem.h"
#include "DropingRewards.h"

Monster::Monster()
	: GameObject(LAYER_TYPE::MONSTER)
	, m_bExtraHitFlag(false)
	, m_bHitFlag(false)
	, m_bDeadFlag(false)
	, m_eMonsterState(MONSTER_STATE::IDLE)
	, m_eMonsterType(MONSTER_TYPE::NORMAL)
{
}

Monster::~Monster()
{
}

void Monster::Awake()
{
	GameObject::Awake();
	m_Status.MonsterDefaultSetting();
	CreateMonsterHPHUD();
	CreateParticleGeneratorAndAddedToScene();
}

void Monster::Start()
{
	GameObject::Start();
	m_eMonsterState = MONSTER_STATE::IDLE;
}

void Monster::Update()
{
	GameObject::Update();
}

void Monster::LateUpdate()
{
	GameObject::LateUpdate();
}

void Monster::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Monster::OnTriggerEnter(shared_ptr<GameObject> pGameObject)
{
}

void Monster::OnTriggerExit(shared_ptr<GameObject> pGameObject)
{
}

int32 Monster::CalculateParticleDirectionToDegree(PARTICLE_DIRECTION eParticleDirection)
{
	switch (eParticleDirection)
	{
	case PARTICLE_DIRECTION::TOP:
		return RANDOM(75, 105);
	case PARTICLE_DIRECTION::RIGHT_TOP:
		return RANDOM(60, 90);
	case PARTICLE_DIRECTION::RIGHT:
		return RANDOM(60, 90);
	case PARTICLE_DIRECTION::RIGHT_BTM:
		return RANDOM(-30, -60);
	case PARTICLE_DIRECTION::BTM:
		return RANDOM(-75, -105);
	case PARTICLE_DIRECTION::LEFT_BTM:
		return RANDOM(120, 150);
	case PARTICLE_DIRECTION::LEFT:
		return RANDOM(-240, -270);
	case PARTICLE_DIRECTION::LEFT_TOP:
		return RANDOM(-240, -270);
	}

	return 0;
}

void Monster::CreateMonsterHPHUD()
{
	m_pMonsterHPHUDFrame = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MonsterHPHUD>(L"Forward", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar_Frame.png", Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUDFrame->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUDFrame->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -1.f));

	m_pMonsterHPHUDFrame->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));

	m_pMonsterHPHUD = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MonsterHPHUD>(L"MonsterHP", L"..\\Resources\\Texture\\HUD\\HealthBar\\Enemy_HealthBar.png",  Conv::BaseToDeclare<Monster>(shared_from_this()));
	m_pMonsterHPHUD->AddComponent(make_shared<MonsterHealthBarShowScript>(m_pMonsterHPHUD));
	m_pMonsterHPHUD->GetTransform()->SetParent(GetTransform());
	m_pMonsterHPHUD->GetTransform()->SetLocalPosition(Vec3(0.f, -50.f, -2.f));
	m_pMonsterHPHUD->GetTransform()->SetLocalScale(Vec3(30.f, 3.f, 1.f));

	m_pMonsterHPHUD->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::CreateDeadEffectAndAddedScene()
{
	shared_ptr<AnimationLocalEffect> pDeadEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");
	pDeadEffect->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Monster_Dead", L"..\\Resources\\Animation\\MonsterCommon\\monster_dead.anim");
	pDeadEffect->GetAnimator()->AddAnimation(L"Monster_Dead", pDeadAnimation);
	pDeadEffect->GetAnimator()->Play(L"Monster_Dead", false);

	pDeadEffect->GetTransform()->SetLocalPosition(GetTransform()->GetPhysicalPosition());
	pDeadEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDeadEffect, eSceneType));
}

void Monster::CreateParticleGeneratorAndAddedToScene()
{
	m_pParticleGenerator = make_shared<GlobalEffect>();
	m_pParticleGenerator->AddComponent(make_shared<Transform>());
	m_pParticleGenerator->GetTransform()->SetParent(GetTransform());
	m_pParticleGenerator->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -1.f));
	m_pParticleGenerator->AddComponent(make_shared<ParticleSystem>());
	m_pParticleGenerator->SetFrustum(false);

	m_pParticleGenerator->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pParticleGenerator, eSceneType));
}

void Monster::SetMonsterHPBarWidthAndUnder(float fWidth, float fUnder)
{
	m_pMonsterHPHUD->GetTransform()->SetLocalPosition(Vec3(0.f, fUnder, -2.f));
	m_pMonsterHPHUD->GetTransform()->SetLocalScale(Vec3(fWidth, 3.f, 1.f));
	m_pMonsterHPHUDFrame->GetTransform()->SetLocalPosition(Vec3(0.f, fUnder, -1.f));
	m_pMonsterHPHUDFrame->GetTransform()->SetLocalScale(Vec3(fWidth + 5.f, 5.f, 1.f));
}

void Monster::ActivateDeadEvent(PARTICLE_DIRECTION eParticleDirection)
{
	ScatterParticles(eParticleDirection);
	
	CreateDeadEffectAndAddedScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::ScatterGold()
{
	int32 iRandCount = RANDOM(1, 5);

	for (int32 i = 0; i < iRandCount; ++i)
	{
		shared_ptr<DropingRewards> pGold = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<DropingRewards>(
			L"Deferred", false,
			ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(10.f, 10.f, 10.f), MassProperties(10.f, 10.f, 1.f));

		pGold->AddComponent(make_shared<Animator>());

		// Gold Spin
		{
			shared_ptr<Animation> pSpinAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Gold_Spin", L"..\\Resources\\Animation\\MonsterCommon\\gold_spin.anim");
			pGold->GetAnimator()->AddAnimation(L"Gold_Spin", pSpinAnimation);
		}

		// Gold Get
		{
			shared_ptr<Animation> pGetAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rewards_Get", L"..\\Resources\\Animation\\MonsterCommon\\gold_get.anim");
			pGold->GetAnimator()->AddAnimation(L"Rewards_Get", pGetAnimation);
		}

		pGold->GetAnimator()->Play(L"Gold_Spin");

		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 90.f;
		pGold->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		int32 iRandomDegree = RANDOM(75, 105);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomForce = RANDOM(400, 600);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pGold->Awake();
		pGold->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pGold->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * static_cast<float>(iRandomForce)));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGold, eSceneType));
	}
}

void Monster::ScatterDarkQuartz()
{
	int32 iRandCount = RANDOM(1, 5);
	const wstring szPath = L"..\\Resources\\Texture\\Sprites\\MonsterCommon\\DarkQuartz\\Image_DarkQuartz_";
	for (int32 i = 0; i < iRandCount; ++i)
	{
		int32 iRandomImageNumber = RANDOM(1, 4);
		wstring szRandomPath = szPath + std::to_wstring(iRandomImageNumber) + L".png";

		shared_ptr<DropingRewards> pDarkQuartz = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<DropingRewards>(
			L"Deferred", false,
			ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(10.f, 10.f, 10.f), MassProperties(10.f, 10.f, 1.f), szRandomPath);

		pDarkQuartz->AddComponent(make_shared<Animator>());

		// Gold Get
		{
			shared_ptr<Animation> pGetAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Rewards_Get", L"..\\Resources\\Animation\\MonsterCommon\\darkquartz_get.anim");
			pDarkQuartz->GetAnimator()->AddAnimation(L"Rewards_Get", pGetAnimation);
		}

		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 90.f;
		pDarkQuartz->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		int32 iRandomDegree = RANDOM(45, 135);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomForce = RANDOM(400, 600);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pDarkQuartz->Awake();
		pDarkQuartz->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pDarkQuartz->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * static_cast<float>(iRandomForce)));

		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pDarkQuartz, eSceneType));
	}
}

void Monster::ActivateDeadEvent(const Vec3& vDir)
{
	ScatterParticles(vDir);
	ScatterGold();
	ScatterDarkQuartz();

	CreateDeadEffectAndAddedScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}

void Monster::ActivateDeadEvent()
{
	ScatterParticles(m_vParticleDir);

	CreateDeadEffectAndAddedScene();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUDFrame, eSceneType));
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(m_pMonsterHPHUD, eSceneType));
}
