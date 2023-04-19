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
#include "JuniorKnight.h"
#include "EventManager.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"

class Player;
class ObjectFactory
{
	DECLARE_SINGLE(ObjectFactory);

public:
	FORCEINLINE void SetPlayer(shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
	template<typename T, typename ... Types>
	shared_ptr<T> CreateObject(const wstring& szMaterialName, bool bApplyGravity,
		ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType = GEOMETRY_TYPE::SPHERE,
		Vec3 vSize = Vec3::Zero, const MassProperties& massProperties = MassProperties(),
		const wstring& szPath = L"", Types ... args);

	template<typename T>
	shared_ptr<T> CreateObjectFromPool(const wstring& szMaterialName, bool bApplyGravity,
		ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType = GEOMETRY_TYPE::SPHERE,
		Vec3 vSize = Vec3::Zero, const MassProperties& massProperties = MassProperties(),
		const wstring& szPath = L"");

	template<typename T, typename ... Types>
	shared_ptr<T> CreateObject(const wstring& szMaterialName, const wstring& szPath = L"", Types ... args);

	template<typename T>
	shared_ptr<T> CreateObjectFromPool(const wstring& szMaterialName, const wstring& szPath = L"");

	template<typename T>
	void CreateMonsterAndAddedScene(const Vec3& vMonsterPos);

private:
	template<typename T>
	inline MONSTER_KIND GetMonsterKind();

	shared_ptr<Monster> CreateJuniorKnight(const Vec3& vMonsterPos);
	void CreateSpawnEffectAndAddedScene(const Vec3& vMonsterPos);
private:
	weak_ptr<Player> m_pPlayer;
};

template<typename T, typename ... Types>
shared_ptr<T> ObjectFactory::CreateObject(const wstring& szMaterialName, bool bApplyGravity, 
	ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vSize, const MassProperties& massProperties,
	const wstring& szPath, Types ... args)
{
	shared_ptr<T> pObject = make_shared<T>(args...);
	pObject->AddComponent(make_shared<Transform>());
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(szMaterialName)->Clone();
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));
	if (!szPath.empty())
	{
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(szPath, szPath);
		pMaterial->SetTexture(0, pTexture);
		pObject->GetTransform()->SetLocalScale(pTexture->GetTexSize());
		if (Vec3::Zero == vSize)
			vSize = pTexture->GetTexSize();
	}

	pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));
	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	pObject->AddComponent(pMeshRenderer);


	pObject->AddComponent(make_shared<RigidBody>(bApplyGravity));
	pObject->AddComponent(make_shared<Collider>());
	pObject->AddComponent(make_shared<DebugRenderer>());

	return pObject;
}

template<typename T>
shared_ptr<T> ObjectFactory::CreateObjectFromPool(const wstring& szMaterialName, bool bApplyGravity,
	ACTOR_TYPE eActorType, GEOMETRY_TYPE eGeometryType, Vec3 vSize, const MassProperties& massProperties, const wstring& szPath)
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
		if (Vec3::Zero == vSize)
			vSize = pTexture->GetTexSize();
	}
	pObject->AddComponent(make_shared<Physical>(eActorType, eGeometryType, vSize, massProperties));

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	pObject->AddComponent(pMeshRenderer);


	pObject->AddComponent(make_shared<RigidBody>(bApplyGravity));
	pObject->AddComponent(make_shared<Collider>());
	pObject->AddComponent(make_shared<DebugRenderer>());

	return pObject;
}

template<typename T, typename ... Types>
shared_ptr<T> ObjectFactory::CreateObject(const wstring& szMaterialName, const wstring& szPath, Types ... args)
{
	shared_ptr<T> pObject = make_shared<T>(args...);
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
shared_ptr<T> ObjectFactory::CreateObjectFromPool(const wstring& szMaterialName, const wstring& szPath)
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

template<typename T>
inline void ObjectFactory::CreateMonsterAndAddedScene(const Vec3& vMonsterPos)
{
	MONSTER_KIND eMonsterKind = GetMonsterKind<T>();
	shared_ptr<Monster> pMonster = nullptr;

	switch (eMonsterKind)
	{
	case MONSTER_KIND::JUNIOR_KNIGHT:
		pMonster = CreateJuniorKnight(vMonsterPos);
		break;
	case MONSTER_KIND::NONE:
		break;
	}

	assert(pMonster);

	pMonster->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMonster, eSceneType));

	CreateSpawnEffectAndAddedScene(vMonsterPos);
}


template<typename T>
inline MONSTER_KIND ObjectFactory::GetMonsterKind()
{
	if constexpr (std::is_same_v<T, JuniorKnight>)
		return MONSTER_KIND::JUNIOR_KNIGHT;
	else
		return MONSTER_KIND::NONE;
}