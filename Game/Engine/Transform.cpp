#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

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
	if (GetPhysical())
	{
		m_PxTransform = PxTransform(Conv::Vec3ToPxVec3(m_vLocalScale), PxQuat(PxIdentity));
	}
}

void Transform::FinalUpdate()
{
	if (GetPhysical())
	{
		m_PxTransform.p = Conv::Vec3ToPxVec3(m_vLocalScale);
	}

	Matrix matScale = Matrix::CreateScale(m_vLocalScale);

	Matrix matRotation = Matrix::CreateRotationX(m_vLocalRotation.x);
	matRotation *= Matrix::CreateRotationY(m_vLocalRotation.y);
	matRotation *= Matrix::CreateRotationZ(m_vLocalRotation.z);

	Matrix matTranslation = Matrix::CreateTranslation(m_vLocalTranslation);

	m_matLocal = matScale * matRotation * matTranslation;
	m_matWorld = m_matLocal;
}

void Transform::PushData(shared_ptr<Camera> pCamera)
{
	TransformParams transformParams = {};
	transformParams.matWVP = m_matWorld * pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix();
	transformParams.matWVPInv = transformParams.matWVP.Invert();

	CONST_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&transformParams, sizeof(transformParams));
}
