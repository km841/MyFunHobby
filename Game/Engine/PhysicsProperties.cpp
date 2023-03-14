#include "pch.h"
#include "PhysicsProperties.h"
#include "Engine.h"

PhysicsProperties::PhysicsProperties(const MassProperties& massProperties)
	: Object(OBJECT_TYPE::PROPERTIES)
	, m_fStaticFriction(massProperties.fStaticFriction)
	, m_fDynamicFriction(massProperties.fDynamicFriction)
	, m_fRestitution(massProperties.fRestitution)
	, m_pMaterial(nullptr)
{
	m_pMaterial = PHYSICS->createMaterial(m_fStaticFriction, m_fDynamicFriction, m_fRestitution);
}

PhysicsProperties::~PhysicsProperties()
{
}

void PhysicsProperties::ApplyToShape(PxShape* pShape)
{
	if (m_pMaterial)
	{
		m_pMaterial->setStaticFriction(m_fStaticFriction);
		m_pMaterial->setDynamicFriction(m_fDynamicFriction);
		m_pMaterial->setRestitution(m_fRestitution);

		pShape->setMaterials(&m_pMaterial, 1);
	}
	
}

void PhysicsProperties::Save(const wstring& szPath)
{
}

void PhysicsProperties::Load(const wstring& szPath)
{
}

void PhysicsProperties::SetStaticFriction(float fFriction)
{
	m_fStaticFriction = fFriction;
	if (m_pMaterial)
		m_pMaterial->setStaticFriction(m_fStaticFriction);
}

void PhysicsProperties::SetDynamicFriction(float fFriction)
{
	m_fDynamicFriction = fFriction;
	if (m_pMaterial)
		m_pMaterial->setDynamicFriction(m_fDynamicFriction);
}

void PhysicsProperties::SetRestitution(float fRestitution)
{
	m_fRestitution = fRestitution;
	if (m_pMaterial)
		m_pMaterial->setRestitution(m_fRestitution);
}
