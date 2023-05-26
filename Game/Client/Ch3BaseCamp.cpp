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


	// UI Event 추가 (입장)
	//auto hud = GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BASECAMP_OPENING);
	GET_SINGLE(InterfaceManager)->Get(HUD_TYPE::BASECAMP_OPENING)->Action();

	// Essence
	//{
	//	shared_ptr<DropEssence> pGameObject = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<DropEssence>(
	//		L"Deferred", false, ACTOR_TYPE::STATIC, GEOMETRY_TYPE::BOX, Vec3(30.f, 30.f, 1.f), MassProperties(), L"..\\Resources\\Texture\\Essence\\Lyweasel\\Lyweasel.png", ESSENCE_KIND::LYWEASEL);

	//	pGameObject->GetTransform()->SetLocalPosition(Vec3(-1200.f, 200.f, 100.f));

	//	pGameObject->Awake();
	//	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	//	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pGameObject, eSceneType));
	//}
}

void Ch3BaseCamp::Exit()
{
	BaseCamp::Exit();
}
