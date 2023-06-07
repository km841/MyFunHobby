#include "pch.h"
#include "Chimera.h"
#include "Resources.h"
#include "SpineResource.h"
#include "Transform.h"
#include "Clock.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Scenes.h"
#include "Scene.h"
#include "ComponentObject.h"
#include "ChimeraSprite.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "ObjectFactory.h"
#include "ObjectRemoveToSceneEvent.h"

Chimera::Chimera()
	: GameObject(LAYER_TYPE::MONSTER)
	, m_pSkeleton(nullptr)
	, m_pAnimationState(nullptr)
	, m_pSpineResource(nullptr)
{
}

Chimera::~Chimera()
{

}

void Chimera::Awake()
{
	GameObject::Awake();
	CreateSpineData();
	CreateChimeraSpritesAndAddedToScene();

}

void Chimera::Start()
{
	GameObject::Start();
}

void Chimera::Update()
{
	GameObject::Update();
	SpineDataUpdate();

}

void Chimera::LateUpdate()
{
	GameObject::LateUpdate();
}

void Chimera::FinalUpdate()
{
	GameObject::FinalUpdate();
	ChimeraSpritesUpdate();
}

void Chimera::Destroy()
{
	if (m_pSkeleton)
	{
		delete m_pSkeleton;
		m_pSkeleton = nullptr;
	}

	if (m_pAnimationState)
	{
		delete m_pAnimationState;
		m_pAnimationState = nullptr;
	}

	m_vChimeraSprites.clear();
}

void Chimera::PlayAnimation(const string& szAnimName, bool bLoop)
{
	m_pAnimationState->setAnimation(0, szAnimName.c_str(), bLoop);
}

void Chimera::CreateChimeraSpritesAndAddedToScene()
{
	for (int32 i = 0; i < CHIMERA_SPRITES_COUNT; ++i)
	{
		shared_ptr<ChimeraSprite> pChimeraSprite = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ChimeraSprite>(L"Forward", L"..\\Resources\\Spine\\chimera.png");
		pChimeraSprite->GetTransform()->SetParent(GetTransform());
		pChimeraSprite->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -i * 0.1f));

		pChimeraSprite->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimeraSprite, SCENE_TYPE::DUNGEON));

		m_vChimeraSprites.push_back(pChimeraSprite);

		if (i == 7)
			pChimeraSprite->Disable();
	}
}

void Chimera::CreateSpineData()
{
	m_pSpineResource = GET_SINGLE(Resources)->LoadSkeletonData(
		"ChimeraSkeleton",
		"..\\Resources\\Spine\\chimera.atlas",
		"..\\Resources\\Spine\\chimera.json");
	m_pSkeleton = new spine::Skeleton(m_pSpineResource->GetSkeletonData());
	assert(m_pSkeleton);

	const Vec3& vMyPos = GetTransform()->GetLocalPosition();
	m_pSkeleton->setX(vMyPos.x);
	m_pSkeleton->setY(vMyPos.y);
	m_pAnimationState = new spine::AnimationState(m_pSpineResource->GetAnimationStateData());
	assert(m_pAnimationState);
}

void Chimera::SpineDataUpdate()
{
	m_pAnimationState->update(WORLD_DELTA_TIME);
	m_pAnimationState->apply(*m_pSkeleton);
	m_pSkeleton->updateWorldTransform();
}

void Chimera::ChimeraSpritesUpdate()
{
	std::vector<uint32> vIndices = { 0, 1, 2, 2, 3, 0 };
	Texture* pTexture = nullptr;
	for (int32 i = 0, n = m_vChimeraSprites.size(); i < n; ++i)
	{
		spine::Slot* pSlot = m_pSkeleton->getDrawOrder()[i];
		spine::Attachment* pAttachment = pSlot->getAttachment();

		if (!pAttachment)
			continue;

		if (pAttachment->getRTTI().isExactly(spine::RegionAttachment::rtti))
		{
			spine::RegionAttachment* pRegionAttachment = (spine::RegionAttachment*)pAttachment;

			std::vector<Vertex> vVertices = CalculateVertexData(pSlot, pRegionAttachment);
			shared_ptr<Mesh> pMesh = make_shared<Mesh>();
			pMesh->Init(vVertices, vIndices);

			m_vChimeraSprites[i].lock()->GetMeshRenderer()->SetMesh(pMesh);
		}
	}
}

std::vector<Vertex> Chimera::CalculateVertexData(spine::Slot* pSlot, spine::RegionAttachment* pRegionAttachment)
{
	std::vector<Vertex> vVertices = {};
	vVertices.resize(4);

	pRegionAttachment->computeWorldVertices(*pSlot, &vVertices[0].vPos.x, 0, sizeof(Vertex) / sizeof(float));
	for (int32 j = 0, l = 0; j < 4; j++, l += 2)
	{
		Vertex& vertex = vVertices[j];
		vertex.vPos.x /= MAGNIFICATION;
		vertex.vPos.y /= MAGNIFICATION;
		vertex.vUV.x = pRegionAttachment->getUVs()[l];
		vertex.vUV.y = pRegionAttachment->getUVs()[l + 1];
	}

	return vVertices;
}
