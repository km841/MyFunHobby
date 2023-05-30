#include "pch.h"
#include "Ch3BaseCamp.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Ch3BeginTower.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "DungeonGateOpenEvent.h"
#include "IfAlwaysTrue.h"
#include "DropEssence.h"
#include "InterfaceManager.h"
#include "HUD.h"
#include "NPC_Spider.h"
#include "Animator.h"
#include "Animation.h"

Ch3BaseCamp::Ch3BaseCamp(const wstring& szMapPath, const wstring& szScriptPath)
	: BaseCamp(szMapPath, szScriptPath)
{
}

Ch3BaseCamp::~Ch3BaseCamp()
{
}

void Ch3BaseCamp::Awake()
{
	BaseCamp::Awake();
}

void Ch3BaseCamp::Start()
{
	BaseCamp::Start();
}

void Ch3BaseCamp::Update()
{
	BaseCamp::Update();
}

void Ch3BaseCamp::LateUpdate()
{
	BaseCamp::LateUpdate();
}

void Ch3BaseCamp::FinalUpdate()
{
	BaseCamp::FinalUpdate();
}

void Ch3BaseCamp::Enter()
{
	BaseCamp::Enter();
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BASECAMP_OPENING)->Action();

	// NPC Spider
	{
		shared_ptr<NPC_Spider> pSpider = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<NPC_Spider>(L"Forward", false,
			ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 10.f), MassProperties());

		pSpider->GetTransform()->SetLocalPosition(Vec3(715.f, 151.f, 100.f));
		pSpider->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Spider_Idle", L"..\\Resources\\Animation\\Spider\\npc_spider_idle.anim");
		pSpider->GetAnimator()->AddAnimation(L"Spider_Idle", pAnimation);
		pSpider->GetAnimator()->Play(L"Spider_Idle");

		pSpider->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSpider, SCENE_TYPE::DUNGEON));
	}
}

void Ch3BaseCamp::Exit()
{
	BaseCamp::Exit();
}
