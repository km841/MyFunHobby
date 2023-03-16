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
	, m_pCallback(nullptr)
{
}

Collider::~Collider()
{
}

void Collider::Awake()
{
	// 렌더링할 물체의 모양을 가진 
	shared_ptr<Physical> pPhysical = GetPhysical();

	if (pPhysical)
	{
		CreateDebugGeometry(pPhysical->GetGeometries());
	}

	m_pCallback = g_pEngine->GetPhysics()->GetDispatcher()->GetSimulationCallback();
}

void Collider::FinalUpdate()
{
}

void Collider::Render()
{

}

void Collider::OnCollision()
{
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

void Collider::CreateDebugBox(Vec3 vHalfSize)
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


