#include "pch.h"
#include "Collider.h"
#include "Engine.h"
#include "ContactCallback.h"
#include "Physical.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Resources.h"
#include "DebugRenderer.h"

Collider::Collider()
	: Component(COMPONENT_TYPE::COLLIDER)
	, m_fRaycastMaxDist(1000.f)
	, m_fRaycastMaxHit(5)
	, m_fPenetDepth(0.f)
{
	m_RaycastHit = {};
	m_SweepHit = {};
	m_OverlapHit = {};
	m_FilterData = {};
}

Collider::~Collider()
{
}

void Collider::Awake()
{
	shared_ptr<Physical> pPhysical = GetPhysical();
	m_FilterData.word0 = 1 << static_cast<uint32>(GetGameObject()->GetLayerType());

	if (pPhysical)
	{
		CreateDebugGeometry(pPhysical->GetGeometries());
		pPhysical->GetShape()->setSimulationFilterData(m_FilterData);
	}
}

void Collider::Update()
{
	if (GetPhysical())
	{
		PxShape* pShape = GetPhysical()->GetShape();
		GetPhysical()->GetShape()->setSimulationFilterData(m_FilterData);
	}
}

void Collider::FinalUpdate()
{
}

void Collider::Render()
{
}

void Collider::OnCollisionEnter(shared_ptr<Collider> pOtherCollider)
{
	GetGameObject()->OnCollisionEnter(pOtherCollider->GetGameObject());
}

void Collider::OnCollisionExit(shared_ptr<Collider> pOtherCollider)
{
	GetGameObject()->OnCollisionExit(pOtherCollider->GetGameObject());
}

void Collider::OnTriggerEnter(shared_ptr<Collider> pOtherCollider)
{
	GetGameObject()->OnTriggerEnter(pOtherCollider->GetGameObject());
}

void Collider::OnTriggerExit(shared_ptr<Collider> pOtherCollider)
{
	GetGameObject()->OnTriggerExit(pOtherCollider->GetGameObject());
}

RaycastResult Collider::Raycast(const Vec3& vOrigin, const Vec3& vDir)
{
	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = GetPhysical()->GetGeometries()->boxGeom;

		bool bResult = PxGeometryQuery::raycast(
			Conv::Vec3ToPxVec3(vOrigin),
			Conv::Vec3ToPxVec3(vDir),
			boxGeom, GetTransform()->GetPxTransform(),
			m_fRaycastMaxDist,
			PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
			m_fRaycastMaxHit,
			&m_RaycastHit);

		return RaycastResult(bResult, Conv::PxVec3ToVec3(m_RaycastHit.position));
	}
		break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry capsuleGeom = GetPhysical()->GetGeometries()->capsuleGeom;

		bool bResult = PxGeometryQuery::raycast(
			Conv::Vec3ToPxVec3(vOrigin),
			Conv::Vec3ToPxVec3(vDir),
			capsuleGeom, GetTransform()->GetPxTransform(),
			m_fRaycastMaxDist,
			PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
			m_fRaycastMaxHit,
			&m_RaycastHit);

		return RaycastResult(bResult, Conv::PxVec3ToVec3(m_RaycastHit.position));
	}
		break;
	}

	return RaycastResult(false, Vec3::Zero);
}

bool Collider::Overlap(const PxGeometry& otherGeom, const PxTransform& otherTransform)
{
	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = GetPhysical()->GetGeometries()->boxGeom;
		return PxGeometryQuery::overlap(boxGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
	}
		break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry capsuleGeom = GetPhysical()->GetGeometries()->capsuleGeom;
		return PxGeometryQuery::overlap(capsuleGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
	}
		break;
	}

	return false;
}

bool Collider::ComputePenetration(const PxGeometry& otherGeom, const PxTransform& otherTransform)
{

	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = GetPhysical()->GetGeometries()->boxGeom;
		return PxGeometryQuery::computePenetration(m_vPenetDir, m_fPenetDepth, boxGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
	}
	break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry capsuleGeom = GetPhysical()->GetGeometries()->capsuleGeom;
		return PxGeometryQuery::computePenetration(m_vPenetDir, m_fPenetDepth, capsuleGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
	}
	break;
	}
	
	return false;
}

void Collider::CreateDebugGeometry(shared_ptr<Geometries> pGeometries)
{
	switch (pGeometries->eGeomType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		const PxBoxGeometry& boxGeom = static_cast<const PxBoxGeometry&>(pGeometries->boxGeom);
		Vec3 vHalfSize = Conv::PxVec3ToVec3(boxGeom.halfExtents);
		CreateDebugBox(vHalfSize);
	}
		break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		const PxCapsuleGeometry& capsuleGeom = static_cast<const PxCapsuleGeometry&>(pGeometries->capsuleGeom);
		float fRadius = capsuleGeom.radius;
		float fHalfHeight = capsuleGeom.halfHeight;
		CreateDebugCapsule(fRadius, fHalfHeight);
	}
		break;

	case GEOMETRY_TYPE::PLANE:
		break;
	}
}

void Collider::CreateDebugBox(const Vec3& vHalfSize)
{
	shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	auto [vVertices, vIndices] = Vertex::CreateBoxVerticesAndIndices(Vec3(1.f, 1.f, 1.f));
	pMesh->Init(vVertices, vIndices);

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"DebugGeometry");

	GetDebugRenderer()->SetMaterial(pMaterial);
	GetDebugRenderer()->SetMesh(pMesh);
}

void Collider::CreateDebugCapsule(float fRadius, float fHalfHeight)
{
	//auto [vVertices, vIndices] = Vertex::CreateHemisphereVerticesAndIndices(fRadius, fHalfHeight);
	//shared_ptr<Mesh> pMesh = make_shared<Mesh>();
	//pMesh->Init(vVertices, vIndices);
	//shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"DebugGeometry");

	//GetDebugRenderer()->SetMaterial(pMaterial);
	//GetDebugRenderer()->SetMesh(pMesh);
}


