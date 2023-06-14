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
#include "MadScientist.h"
#include "Animator.h"
#include "Animation.h"
#include "ChimeraRoar.h"
#include "InterfaceManager.h"
#include "BossOpeningHUD.h"
#include "Engine.h"
#include "ChimeraFallParticlesScript.h"
#include "Player.h"
#include "ChimeraFallingObject.h"

Chimera* Chimera::s_pChimera = {};

Chimera::Chimera(shared_ptr<MadScientist> pMadScientist)
	: m_pSkeleton(nullptr)
	, m_pAnimationState(nullptr)
	, m_pSpineResource(nullptr)
	, m_pMadScientist(pMadScientist)
{
	s_pChimera = this;
	m_eMonsterState = MONSTER_STATE::RAGE_ATTACK_END;
	m_eMonsterType = MONSTER_TYPE::NONE_HIT;
}

Chimera::~Chimera()
{

}

void Chimera::Awake()
{
	GameObject::Awake();
	CreateSpineData();
	CreateChimeraSpritesAndAddedToScene();
	CreateParticleGeneratorAndAddedToScene();
	m_Status.BossMonsterDefaultSetting();

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

void Chimera::Enable()
{
	GameObject::Enable();
	for (int32 i = 0; i < m_vChimeraSprites.size(); ++i)
	{
		m_vChimeraSprites[i].lock()->Enable();
	}
}

void Chimera::Disable()
{
	for (int32 i = 0; i < m_vChimeraSprites.size(); ++i)
	{
		m_vChimeraSprites[i].lock()->Disable();
	}
	GameObject::Disable();
}


void Chimera::Listener(spine::AnimationState* state, spine::EventType type, spine::TrackEntry* entry, spine::Event* event)
{
	const spine::String& animationName = (entry && entry->getAnimation()) ? entry->getAnimation()->getName() : spine::String("");
	assert(!animationName.isEmpty());
	string szAnimName = animationName.buffer();
	

	switch (type)
	{
	case spine::EventType_Start:
	{
		s_pChimera->SetCurAnimationName(szAnimName);
		if ("Appear" == szAnimName)
		{
			static_pointer_cast<BossOpeningHUD>(GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::BOSS_OPENING))->SetStageKind(STAGE_KIND::BLACK_LAB);
			GET_SINGLE(InterfaceManager)->Get(INTERFACE_TYPE::BOSS_OPENING)->Action();
			s_pChimera->DestroyMadScientist();
			s_pChimera->DropParticles();
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(1.f, Vec3(1000, 1000.f, 0.f));
		}

		if ("Roar_Skill_Loop" == szAnimName)
		{
			s_pChimera->CreateRoarAndAddedToScene();
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(1.f, Vec3(1000, 1000.f, 0.f));
		}

		if ("Roar_Loop" == szAnimName)
		{
			s_pChimera->CreateRoarAndAddedToScene();
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(1.f, Vec3(1000, 1000.f, 0.f));
			GET_SINGLE(Scenes)->GetActiveScene()->RegisterSceneEvent(EVENT_TYPE::ACTIVATE_DISTORTION, 0, 2.f);
		}

		if ("Grab_Smash" == szAnimName)
		{
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(1.f, Vec3(1000, 3000.f, 0.f));
		}
	}
		break;
	case spine::EventType_Interrupt:
		break;
	case spine::EventType_End:
		break;
	case spine::EventType_Complete:
	{
		if ("Breath_End" == szAnimName)
		{
			GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(1.f, Vec3(1000, 3000.f, 0.f));
			s_pChimera->BreakFallingObject();

			auto& vFallingObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::FALLING_OBJECT);
			for (auto& pFallingObject : vFallingObjects)
			{
				static_pointer_cast<ChimeraFallingObject>(pFallingObject)->SetDestroy();
			}
			// Breaking
		}
	}
		break;
	case spine::EventType_Dispose:
		break;
	case spine::EventType_Event:
		break;
	}
	fflush(stdout);
}

void Chimera::PlayAnimation(const string& szAnimName, bool bLoop)
{
	m_pAnimationState->setAnimation(0, szAnimName.c_str(), bLoop);
	m_szCurAnimationName = szAnimName;
}

void Chimera::AddAnimation(const string& szAnimName, float fDelay, bool bLoop)
{
	bool bFlag = true;
	for (int32 i = 0; i < m_pAnimationState->getTracks().size(); ++i)
	{
		spine::String szName = m_pAnimationState->getTracks()[i]->getAnimation()->getName();
		if (string(szName.buffer()) == szAnimName)
			bFlag = false;
	}
	
	if (bFlag)
	{
		m_pAnimationState->addAnimation(0, szAnimName.c_str(), bLoop, fDelay);
	}
}

void Chimera::DestroyMadScientist()
{
	m_pMadScientist.lock()->Destroy();
}

void Chimera::DropParticles()
{
	const float fTopY = static_cast<float>(g_pEngine->GetHeight());

	const wstring szResourcePath = L"..\\Resources\\Texture\\Sprites\\Chimera\\Image_Fall_Particle0";
	Vec3 vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();

	for (int32 i = 1; i <= 20; ++i)
	{
		wstring szFullPath = szResourcePath + std::to_wstring(RANDOM(1, 8)) + L".png";
		shared_ptr<GameObject> pGameObject = 
			GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<GameObject>(L"Forward", false, ACTOR_TYPE::DYNAMIC, GEOMETRY_TYPE::BOX, Vec3(10.f, 10.f, 1.f), MassProperties(), szFullPath, LAYER_TYPE::UNKNOWN);
		pGameObject->AddComponent(make_shared<ChimeraFallParticlesScript>());

		Vec3 vObjectPos = vPlayerPos;
		vObjectPos.x += static_cast<float>(RANDOM(-500, 500));
		vObjectPos.y += static_cast<float>(RANDOM(400, 1000));
		vObjectPos.z -= 1.f;
		pGameObject->GetTransform()->SetLocalPosition(vObjectPos);

		pGameObject->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, SCENE_TYPE::DUNGEON));
	}
}

void Chimera::BreakFallingObject()
{
}

void Chimera::CreateRoarAndAddedToScene()
{
	shared_ptr<ChimeraRoar> pChimeraRoar = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ChimeraRoar>(L"Forward");
	pChimeraRoar->GetTransform()->SetParent(GetTransform());
	pChimeraRoar->GetTransform()->SetLocalPosition(Vec3(-200.f, 350.f, 0.f));
	pChimeraRoar->AddComponent(make_shared<Animator>());
	// Chimera Roar
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Chimera_Roar", L"..\\Resources\\Animation\\Chimera\\chimera_roar.anim");
		pChimeraRoar->GetAnimator()->AddAnimation(L"Chimera_Roar", pAnimation);
		pChimeraRoar->GetAnimator()->Play(L"Chimera_Roar");
	}

	pChimeraRoar->Awake();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimeraRoar, SCENE_TYPE::DUNGEON));
}

void Chimera::CreateChimeraSpritesAndAddedToScene()
{
	for (int32 i = 0; i < CHIMERA_SPRITES_COUNT; ++i)
	{
		shared_ptr<ChimeraSprite> pChimeraSprite = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<ChimeraSprite>(L"Forward", L"..\\Resources\\Spine\\chimera.png");
		pChimeraSprite->GetTransform()->SetParent(GetTransform());
		pChimeraSprite->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -i * 0.1f));
		pChimeraSprite->GetTransform()->SetLocalScale(Vec3(350.f, 350.f, 1.f));
		pChimeraSprite->GetTransform()->SetGlobalOffset(Vec2(-800.f, -270.f));

		pChimeraSprite->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimeraSprite, SCENE_TYPE::DUNGEON));

		m_vChimeraSprites.push_back(pChimeraSprite);
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
	m_pAnimationState->setListener(Listener);
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
	for (size_t i = 0, n = m_vChimeraSprites.size(); i < n; ++i)
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
