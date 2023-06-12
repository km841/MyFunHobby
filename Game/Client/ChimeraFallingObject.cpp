#include "pch.h"
#include "ChimeraFallingObject.h"
#include "RigidBody.h"

ChimeraFallingObject::ChimeraFallingObject()
	: GameObject(LAYER_TYPE::FALLING_OBJECT)
	, m_bChecked(false)
	, m_bTriggerFlag(false)
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
			GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, 0.f));
			GetRigidBody()->SetRotationZForDynamic(0.f);
			GetRigidBody()->SetAngularDamping(PX_MAX_F32);
			GetRigidBody()->SetLinearDamping(PX_MAX_F32);
			m_bChecked = true;
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