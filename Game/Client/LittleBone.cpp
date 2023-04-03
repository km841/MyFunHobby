#include "pch.h"
#include "LittleBone.h"
#include "PlayerProjectile.h"
#include "Physical.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "DebugRenderer.h"
#include "Movement.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Resources.h"
#include "Scenes.h"
#include "Scene.h"
#include "RotateHeadScript.h"

LittleBone::LittleBone()
	: Skul(SKUL_GRADE::NORMAL)
	, m_eLittleBoneState(LITTLE_BONE_STATE::HAS_HEAD)
{
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
	
}

void LittleBone::Awake()
{
	Skul::Awake();
	CreateHeadAndAddedToScene();
}

void LittleBone::Start()
{
	Skul::Start();
}

void LittleBone::Update()
{
	Skul::Update();
}

void LittleBone::LateUpdate()
{
	Skul::LateUpdate();
}

void LittleBone::FinalUpdate()
{
	Skul::FinalUpdate();
}

void LittleBone::LoseHead()
{
	m_eLittleBoneState = LITTLE_BONE_STATE::NO_HEAD;
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
}

void LittleBone::PickUpHead()
{
	m_eLittleBoneState = LITTLE_BONE_STATE::HAS_HEAD;
	SetEnumIndex(static_cast<uint8>(m_eLittleBoneState));
}

void LittleBone::CreateHeadAndAddedToScene()
{
	m_pHead = make_shared<PlayerProjectile>();
	m_pHead->Disable();

	m_pHead->AddComponent(make_shared<Transform>());
	m_pHead->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(15.f, 13.f, 1.f)));
	m_pHead->AddComponent(make_shared<Collider>());
	m_pHead->AddComponent(make_shared<DebugRenderer>());
	m_pHead->AddComponent(make_shared<RigidBody>());
	m_pHead->AddComponent(make_shared<Movement>());
	m_pHead->AddComponent(make_shared< RotateHeadScript>(m_pHead));

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"LittleBone_Head", L"..\\Resources\\Texture\\Sprites\\LittleBone\\Image_LittleBone_Head.tga");
	pMaterial->SetTexture(0, pTexture);

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	m_pHead->GetTransform()->SetLocalScale(pTexture->GetTexSize());
	m_pHead->AddComponent(pMeshRenderer);

	m_pHead->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHead, eSceneType));
}
