#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"
#include "Physical.h"
#include "GameObject.h"
#include "Animator.h"
#include "Animation.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
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
		m_PxTransform = GetPhysical()->GetActor<PxRigidActor>()->getGlobalPose();

		Matrix matPxScale = Matrix::CreateScale(GetPhysical()->GetGeometrySize());
		Matrix matPxRotation = Matrix::CreateFromQuaternion(Conv::PxQuatToQuat(m_PxTransform.q));
		Matrix matPxTranslation = Matrix::CreateTranslation(Conv::PxVec3ToVec3(m_PxTransform.p));
		m_matPxWorld = matPxScale * matPxRotation * matPxTranslation;

		Vec3 vLocalTranslation = Vec3(
			m_PxTransform.p.x + m_vGlobalOffset.x, 
			m_PxTransform.p.y + m_vGlobalOffset.y, 
			m_PxTransform.p.z);

		Matrix matTranslation = Matrix::CreateTranslation(vLocalTranslation);
		Matrix matScale = Matrix::CreateScale(m_vLocalScale);
		m_matWorld = matScale * matPxRotation * matTranslation;
	}

	else
	{
		Matrix matScale = Matrix::CreateScale(m_vLocalScale);

		Matrix matRotation = Matrix::CreateRotationX(m_vLocalRotation.x);
		matRotation *= Matrix::CreateRotationY(m_vLocalRotation.y);
		matRotation *= Matrix::CreateRotationZ(m_vLocalRotation.z);

		Vec3 vLocalTranslation = m_vLocalTranslation + Vec3(m_vGlobalOffset.x, m_vGlobalOffset.y, 0.f);
		Matrix matTranslation = Matrix::CreateTranslation(vLocalTranslation);

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
	transformParams.matWorld = m_matWorld;
	transformParams.matView = pCamera->GetViewMatrix();
	transformParams.matProjection = pCamera->GetProjectionMatrix();
	transformParams.matWV = m_matWorld * pCamera->GetViewMatrix();
	transformParams.matWVP = m_matWorld * pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix();
	transformParams.matWVPInv = transformParams.matWVP.Invert();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}

void Transform::PxPushData(shared_ptr<Camera> pCamera)
{
	TransformParams transformParams = {};
	transformParams.matWorld = m_matWorld;
	transformParams.matView = pCamera->GetViewMatrix();
	transformParams.matProjection = pCamera->GetProjectionMatrix();
	transformParams.matWV = m_matWorld * pCamera->GetViewMatrix();
	transformParams.matWVP = m_matPxWorld * pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix();
	transformParams.matWVPInv = transformParams.matWVP.Invert();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}

Vec3 Transform::GetWorldPosition()
{
	//if (m_pParent.lock())
	//{
	//	Matrix matParentMatrix = m_pParent.lock()->GetLocalToWorldMatrix();
	//	matParentMatrix._11 = 1.f;
	//	matParentMatrix._22 = 1.f;
	//	matParentMatrix._33 = 1.f;
	//	Matrix matWorld = m_matWorld *= matParentMatrix;
	//	return matWorld.Translation();
	//}
	//else
	{
		return m_matWorld.Translation();
	}
}

void Transform::SetPhysicalPosition(const Vec3& vPosition)
{
	assert(GetPhysical());
	m_PxTransform.p = Conv::Vec3ToPxVec3(vPosition);
	GetPhysical()->GetActor<PxRigidActor>()->setGlobalPose(m_PxTransform);
}

Vec3 Transform::GetPhysicalPosition()
{
	assert(GetPhysical());
	return Conv::PxVec3ToVec3(GetPhysical()->GetActor<PxRigidActor>()->getGlobalPose().p);
}
