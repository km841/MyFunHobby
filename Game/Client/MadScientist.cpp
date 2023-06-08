#include "pch.h"
#include "MadScientist.h"
#include "RigidBody.h"
#include "Physical.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Particle.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "ObjectRemoveToSceneEvent.h"

MadScientist::MadScientist()
	: GameObject(LAYER_TYPE::NPC)
{
}

MadScientist::~MadScientist()
{
}

void MadScientist::Awake()
{
	GameObject::Awake();

	wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\MadScientist\\";
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist01.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist02.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist03.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist04.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist05.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist06.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist07.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist08.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist09.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist10.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist11.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist12.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist13.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist14.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist15.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist16.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist17.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist18.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist19.png");
	m_vTextureNames.push_back(szResourcePath + L"Image_MadScientist20.png");

}

void MadScientist::Start()
{
	GameObject::Start();
}

void MadScientist::Update()
{
	GameObject::Update();
}

void MadScientist::LateUpdate()
{
	GameObject::LateUpdate();
}

void MadScientist::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void MadScientist::Destroy()
{
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	for (int32 i = 0; i < m_vTextureNames.size(); ++i)
	{
		shared_ptr<Particle> pParticle = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<Particle>(
			L"Deferred", false,
			ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3::Zero, MassProperties(10.f, 10.f, 1.f),
			m_vTextureNames[i]);

		Vec3 vMyPos = GetTransform()->GetWorldPosition();
		vMyPos.z = 101.f;
		vMyPos.x -= RANDOM(0, 100);
		pParticle->GetTransform()->SetLocalPosition(vMyPos);

		Vec3 vRightNormal = VEC3_RIGHT_NORMAL;

		int32 iRandomDegree = RANDOM(80, 100);
		float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;
		float fRotatedX = vRightNormal.x * cosf(fRandomRadian) - vRightNormal.y * sinf(fRandomRadian);
		float fRotatedY = vRightNormal.x * sinf(fRandomRadian) + vRightNormal.y * cosf(fRandomRadian);

		int32 iRandomAngularVelocity = RANDOM(-30, 30);
		Vec3 vRotatedVec = Vec3(fRotatedX, fRotatedY, 0.f);
		pParticle->Awake();
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setAngularVelocity(PxVec3(0.f, 0.f, static_cast<float>(iRandomAngularVelocity)));
		pParticle->GetPhysical()->GetActor<PxRigidDynamic>()->setLinearVelocity(Conv::Vec3ToPxVec3(vRotatedVec * 800.f));

		
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pParticle, eSceneType));
	}

	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(shared_from_this(), eSceneType));
}
