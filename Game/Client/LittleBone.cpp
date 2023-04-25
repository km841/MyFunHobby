#include "pch.h"
#include "LittleBone.h"
#include "LittleBoneHead.h"
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
#include "Player.h"
#include "GlobalEffect.h"
#include "ParticleSystem.h"
#include "ObjectFactory.h"

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

void LittleBone::CooldownCompletionCallback(SKILL_INDEX eSkillIndex)
{
	if (SKILL_INDEX::FIRST == eSkillIndex)
	{
		PickUpHead();
		m_pHead->Disable();
		m_pPlayer.lock()->RefreshAnimation();
	}

}

void LittleBone::CreateHeadAndAddedToScene()
{
	m_pHead = GET_SINGLE(ObjectFactory)->CreateObjectHavePhysical<LittleBoneHead>(
		L"Deferred", false,
		ACTOR_TYPE::PROJECTILE_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(15.f, 13.f, 10.f), MassProperties(0.3f, 0.3f, 1.f),
		L"..\\Resources\\Texture\\Sprites\\LittleBone\\Image_LittleBone_Head.tga");

	m_pHead->AddComponent(make_shared<Movement>());
	m_pHead->AddComponent(make_shared<RotateHeadScript>(m_pHead));

	m_pHead->Disable();
	m_pHead->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(m_pHead, eSceneType));
}


