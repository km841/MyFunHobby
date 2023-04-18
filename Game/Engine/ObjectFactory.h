#pragma once
#include "Transform.h"
#include "Physical.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"
#include "GameObject.h"
#include "Collider.h"
#include "RigidBody.h"
#include "DebugRenderer.h"
#include "Texture.h"
#include "Movement.h"

class ObjectFactory
{
	DECLARE_SINGLE(ObjectFactory);

public:
	template<typename T>
	shared_ptr<T> CreateObject(const wstring& szMaterialName, 
		bool bApplyGravity,
		ACTOR_TYPE eActorType = ACTOR_TYPE::KINEMATIC, 
		GEOMETRY_TYPE eGeometryType = GEOMETRY_TYPE::SPHERE, 
		const Vec3& vSize = Vec3(50.f, 50.f, 1.f),
		const MassProperties& massProperties = MassProperties(),
		const wstring& szPath = L"")
	{
		shared_ptr<T> pObject = make_shared<T>();
		pObject->AddComponent(make_shared<Transform>());
		pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(szMaterialName)->Clone();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		if (!szPath.empty())
		{
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
			pMaterial->SetTexture(0, pTexture);
			pObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());
			pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, pTexture->GetTexSize(), massProperties));
		}
		else
		{
			pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));
		}

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pObject->AddComponent(pMeshRenderer);

		pObject->AddComponent(make_shared<RigidBody>(bApplyGravity));
		pObject->AddComponent(make_shared<Collider>());
		pObject->AddComponent(make_shared<DebugRenderer>());
		pObject->AddComponent(make_shared<Movement>());

		return pObject;
	}

	template<typename T>
	shared_ptr<T> CreateObjectFromPool(const wstring& szMaterialName,
		bool bApplyGravity,
		ACTOR_TYPE eActorType = ACTOR_TYPE::KINEMATIC,
		GEOMETRY_TYPE eGeometryType = GEOMETRY_TYPE::SPHERE,
		const Vec3& vSize = Vec3(50.f, 50.f, 1.f),
		const MassProperties& massProperties = MassProperties(),
		const wstring& szPath = L"")
	{
		shared_ptr<T> pObject = T::Get();
		pObject->AddComponent(make_shared<Transform>());
		
		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(szMaterialName)->Clone();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		if (!szPath.empty())
		{
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
			pMaterial->SetTexture(0, pTexture);
			pObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());
			pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, pTexture->GetTexSize(), massProperties));
		}
		else
		{
			pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));
		}

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pObject->AddComponent(pMeshRenderer);

		pObject->AddComponent(make_shared<RigidBody>(bApplyGravity));
		pObject->AddComponent(make_shared<Collider>());
		pObject->AddComponent(make_shared<DebugRenderer>());
		pObject->AddComponent(make_shared<Movement>());

		return pObject;
	}


	template<typename T>
	shared_ptr<T> CreateObject(const wstring& szMaterialName, const wstring& szPath = L"")
	{
		shared_ptr<T> pObject = make_shared<T>();
		pObject->AddComponent(make_shared<Transform>());

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(szMaterialName)->Clone();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		if (!szPath.empty())
		{
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
			pMaterial->SetTexture(0, pTexture);
			pObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());
		}

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pObject->AddComponent(pMeshRenderer);

		return pObject;
	}

	template<typename T>
	shared_ptr<T> CreateObjectFromPool(const wstring& szMaterialName, const wstring& szPath = L"")
	{
		shared_ptr<T> pObject = T::Get();
		pObject->AddComponent(make_shared<Transform>());

		shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(szMaterialName)->Clone();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

		if (!szPath.empty())
		{
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
			pMaterial->SetTexture(0, pTexture);
			pObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());
		}

		shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
		pMeshRenderer->SetMaterial(pMaterial);
		pMeshRenderer->SetMesh(pMesh);
		pObject->AddComponent(pMeshRenderer);

		return pObject;
	}

private:

};

