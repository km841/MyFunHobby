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
#include "Clock.h"

Collider::Collider()
	: Component(COMPONENT_TYPE::COLLIDER)
	, m_fMaxDist(1000.f)
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
	m_FilterData.word0 = 1 << static_cast<uint32>(GetGameObject()->GetLayerType());

	if (GetPhysical())
	{
		if (GetDebugRenderer())
			CreateDebugGeometry(GetPhysical()->GetGeometries());

		GetPhysical()->GetShape()->setSimulationFilterData(m_FilterData);
	}
}

void Collider::Update()
{
	if (GetPhysical())
	{
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

void Collider::OnTriggerStay(shared_ptr<Collider> pOtherCollider)
{
	int a = 0;
}

void Collider::OnTriggerExit(shared_ptr<Collider> pOtherCollider)
{
	GetGameObject()->OnTriggerExit(pOtherCollider->GetGameObject());
}

bool Collider::Raycast(const Vec3& vOrigin, const Vec3& vDir, shared_ptr<GameObject> pGameObject, float fMaxDistance)
{
	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();
	if (!pGameObject->GetPhysical())
	{
		return false;
	}

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = pGameObject->GetPhysical()->GetGeometries()->boxGeom;
		PxTransform transform = pGameObject->GetTransform()->GetPxTransform();

		bool bResult = PxGeometryQuery::raycast(
			Conv::Vec3ToPxVec3(vOrigin),
			Conv::Vec3ToPxVec3(vDir),
			boxGeom, transform,
			fMaxDistance,
			PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
			m_fRaycastMaxHit,
			&m_RaycastHit);

		return bResult;
	}
		break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry capsuleGeom = pGameObject->GetPhysical()->GetGeometries()->capsuleGeom;
		PxTransform transform = pGameObject->GetTransform()->GetPxTransform();

		bool bResult = PxGeometryQuery::raycast(
			Conv::Vec3ToPxVec3(vOrigin),
			Conv::Vec3ToPxVec3(vDir),
			capsuleGeom, transform,
			m_fMaxDist,
			PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
			m_fRaycastMaxHit,
			&m_RaycastHit);

		return bResult;
	}
		break;

	case GEOMETRY_TYPE::SPHERE:
	{
		PxSphereGeometry sphereGeom = pGameObject->GetPhysical()->GetGeometries()->sphereGeom;
		PxTransform transform = pGameObject->GetTransform()->GetPxTransform();

		bool bResult = PxGeometryQuery::raycast(
			Conv::Vec3ToPxVec3(vOrigin),
			Conv::Vec3ToPxVec3(vDir),
			sphereGeom, transform,
			m_fMaxDist,
			PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
			m_fRaycastMaxHit,
			&m_RaycastHit);

		return bResult;
	}
	break;
	}

	return false;
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

bool Collider::Sweep( const PxGeometry& otherGeom, const PxTransform& otherTransform)
{
	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();
	const Vec3& vMyPos = GetTransform()->GetLocalPosition();
	const PxVec3& vOtherPos = otherTransform.p;

	const PxVec3& vDir = vOtherPos - Conv::Vec3ToPxVec3(vMyPos);
	PxVec3 vUnitDir = vDir.getNormalized();

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = GetPhysical()->GetGeometries()->boxGeom;
		return PxGeometryQuery::sweep(vUnitDir, m_fMaxDist, boxGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform, m_SweepHit);
	}
	break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry capsuleGeom = GetPhysical()->GetGeometries()->capsuleGeom;
		return PxGeometryQuery::sweep(vUnitDir, m_fMaxDist, capsuleGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform, m_SweepHit);
	}
	break;
	}

	return false;
}

Vec3 Collider::ComputePenetration(shared_ptr<GameObject> pGameObject)
{
	GEOMETRY_TYPE eGeometryType = GetPhysical()->GetGeometryType();
	if (!pGameObject->GetPhysical())
		return Vec3::Zero;

	switch (eGeometryType)
	{
	case GEOMETRY_TYPE::BOX:
	{
		PxBoxGeometry boxGeom = GetPhysical()->GetGeometries()->boxGeom;
		PxBoxGeometry otherGeom = pGameObject->GetPhysical()->GetGeometries()->boxGeom;
		PxTransform otherTransform = pGameObject->GetPhysical()->GetActor<PxRigidActor>()->getGlobalPose();

		bool bIsPenet = PxGeometryQuery::computePenetration(m_vPenetDir, m_fPenetDepth, boxGeom, GetPhysical()->GetActor<PxRigidActor>()->getGlobalPose(), otherGeom, otherTransform);
		if (bIsPenet)
			return Conv::PxVec3ToVec3(m_vPenetDir * m_fPenetDepth);
	}
	break;

	case GEOMETRY_TYPE::CAPSULE:
	{
		PxCapsuleGeometry otherGeom = pGameObject->GetPhysical()->GetGeometries()->capsuleGeom;
		PxTransform otherTransform = pGameObject->GetTransform()->GetPxTransform();
		PxCapsuleGeometry capsuleGeom = GetPhysical()->GetGeometries()->capsuleGeom;
		bool bIsPenet = PxGeometryQuery::computePenetration(m_vPenetDir, m_fPenetDepth, capsuleGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
		if (bIsPenet)
			return Conv::PxVec3ToVec3(m_vPenetDir * m_fPenetDepth);
	}
	break;

	case GEOMETRY_TYPE::SPHERE:
	{
		PxSphereGeometry otherGeom = pGameObject->GetPhysical()->GetGeometries()->sphereGeom;
		PxTransform otherTransform = pGameObject->GetTransform()->GetPxTransform();
		PxSphereGeometry capsuleGeom = GetPhysical()->GetGeometries()->sphereGeom;
		bool bIsPenet = PxGeometryQuery::computePenetration(m_vPenetDir, m_fPenetDepth, capsuleGeom, GetTransform()->GetPxTransform(), otherGeom, otherTransform);
		if (bIsPenet)
			return Conv::PxVec3ToVec3(m_vPenetDir * m_fPenetDepth);
	}
	break;
	}
	
	return Vec3::Zero;
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
		CreateDebugBox(Vec3(fRadius, fRadius, 1.f));
	}
		break;

	case GEOMETRY_TYPE::SPHERE:
	{
		const PxCapsuleGeometry& capsuleGeom = static_cast<const PxCapsuleGeometry&>(pGeometries->capsuleGeom);
		float fRadius = capsuleGeom.radius;
		float fHalfHeight = capsuleGeom.halfHeight;
		CreateDebugBox(Vec3(fRadius, fRadius, 1.f));
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

