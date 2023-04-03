#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"
#include "Physical.h"
#include "GameObject.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
	, m_bChanged(false)
{
}

Transform::~Transform()
{
}

void Transform::Awake()
{
	m_PxTransform.p = Conv::Vec3ToPxVec3(m_vLocalTranslation);
	m_PxTransform.q = PxQuat(PxIdentity);
}

void Transform::FinalUpdate()
{
	if (GetPhysical())
	{
		ACTOR_TYPE eActorType = GetPhysical()->GetActorType();

		switch (eActorType)
		{
			case ACTOR_TYPE::STATIC:
				m_PxTransform = GetPhysical()->GetActor<PxRigidStatic>()->getGlobalPose();
				break;

			case ACTOR_TYPE::KINEMATIC:
			case ACTOR_TYPE::DYNAMIC:
				m_PxTransform = GetPhysical()->GetActor<PxRigidDynamic>()->getGlobalPose();
				break;

			case ACTOR_TYPE::CHARACTER:
				m_PxTransform = GetPhysical()->GetController()->getActor()->getGlobalPose();
				m_PxTransform.q.z = 0.f;
				break;
		}

		m_vPxLocalScale = Conv::Vec3ToPxVec3(GetPhysical()->GetGeometrySize());
		m_vPxLocalRotation = static_cast<PxMat33>(m_PxTransform.q.getNormalized());
		m_vPxLocalTranslation = m_PxTransform.p;

		Matrix matPxScale = Matrix::CreateScale(Conv::PxVec3ToVec3(m_vPxLocalScale));
		Matrix matPxRotation = Matrix::CreateRotationZ(m_PxTransform.q.z + m_vLocalRotation.z);
		Matrix matPxTranslation = Matrix::CreateTranslation(Conv::PxVec3ToVec3(m_vPxLocalTranslation));

		m_matPxWorld = matPxScale * matPxRotation * matPxTranslation;

		Matrix matScale = Matrix::CreateScale(m_vLocalScale);
		m_matWorld = matScale * matPxRotation * matPxTranslation;
	}

	else
	{
		Matrix matScale = Matrix::CreateScale(m_vLocalScale);

		Matrix matRotation = Matrix::CreateRotationX(m_vLocalRotation.x);
		matRotation *= Matrix::CreateRotationY(m_vLocalRotation.y);
		matRotation *= Matrix::CreateRotationZ(m_vLocalRotation.z);

		Matrix matTranslation = Matrix::CreateTranslation(m_vLocalTranslation);

		m_matLocal = matScale * matRotation * matTranslation;
		m_matWorld = m_matLocal;
	}

	if (m_pParent.lock())
	{
		Matrix matParentMatrix = m_pParent.lock()->GetLocalToWorldMatrix();
		matParentMatrix._11 = 1.f;
		matParentMatrix._22 = 1.f;
		matParentMatrix._33 = 1.f;
		m_matWorld *= matParentMatrix;
		GetGameObject()->SetDirection(m_pParent.lock()->GetGameObject()->GetDirection());
	}
}

void Transform::PushData(shared_ptr<Camera> pCamera)
{
	TransformParams transformParams = {};
	transformParams.matWVP = m_matWorld * pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix();
	transformParams.matWVPInv = transformParams.matWVP.Invert();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}

void Transform::PxPushData(shared_ptr<Camera> pCamera)
{
	TransformParams transformParams = {};
	transformParams.matWVP = m_matPxWorld * pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix();
	transformParams.matWVPInv = transformParams.matWVP.Invert();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}
