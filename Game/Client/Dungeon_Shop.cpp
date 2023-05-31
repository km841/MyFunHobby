#include "pch.h"
#include "Dungeon_Shop.h"
#include "DecoObject.h"
#include "ObjectFactory.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Resources.h"
#include "Transform.h"
#include "EventManager.h"
#include "Animator.h"
#include "Animation.h"

Dungeon_Shop::Dungeon_Shop(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::SHOP, szMapPath, szScriptPath)
{
}

Dungeon_Shop::~Dungeon_Shop()
{
}

void Dungeon_Shop::Awake()
{
	Dungeon::Awake();
}

void Dungeon_Shop::Start()
{
	Dungeon::Start();
}

void Dungeon_Shop::Update()
{
	Dungeon::Update();
}

void Dungeon_Shop::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Dungeon_Shop::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Dungeon_Shop::Enter()
{
	Dungeon::Enter();

	// Apply Shop Objects!
	// Pub
	{
		shared_ptr<DecoObject> pPub = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<DecoObject>(L"Deferred", L"..\\Resources\\Texture\\DecoObject\\Image_Shop_Pub.png");
		pPub->GetTransform()->SetLocalPosition(Vec3(100.f, 460.f, 101.f));

		pPub->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pPub, SCENE_TYPE::DUNGEON));
	}

	// Food 
	{
		shared_ptr<GameObject> pFoodShop = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
		pFoodShop->GetTransform()->SetLocalPosition(Vec3(-125.f, 600.f, 100.5f));

		pFoodShop->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"FoodShop_Idle", L"..\\Resources\\Animation\\Shop\\shop_food_idle.anim");
		pFoodShop->GetAnimator()->AddAnimation(L"FoodShop_Idle", pAnimation);
		pFoodShop->GetAnimator()->Play(L"FoodShop_Idle");

		pFoodShop->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pFoodShop, SCENE_TYPE::DUNGEON));
	}

	// Struct
	{
		shared_ptr<GameObject> pStruct = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
		pStruct->GetTransform()->SetLocalPosition(Vec3(480.f, 700.f, 102.f));

		pStruct->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Struct_Idle", L"..\\Resources\\Animation\\Shop\\shop_struct_idle.anim");
		pStruct->GetAnimator()->AddAnimation(L"Struct_Idle", pAnimation);
		pStruct->GetAnimator()->Play(L"Struct_Idle");

		pStruct->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pStruct, SCENE_TYPE::DUNGEON));
	}

	// Struct
	{
		shared_ptr<GameObject> pChimney = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
		pChimney->GetTransform()->SetLocalPosition(Vec3(1180.f, 650.f, 101.f));

		pChimney->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Chimney_Idle", L"..\\Resources\\Animation\\Shop\\shop_chimney_idle.anim");
		pChimney->GetAnimator()->AddAnimation(L"Chimney_Idle", pAnimation);
		pChimney->GetAnimator()->Play(L"Chimney_Idle");

		pChimney->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimney, SCENE_TYPE::DUNGEON));
	}

	// Exhibition
	{
		shared_ptr<GameObject> pExhibition = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<GameObject>(L"Forward", L"", LAYER_TYPE::UNKNOWN);
		pExhibition->GetTransform()->SetLocalPosition(Vec3(730.f, 365.f, 100.f));

		pExhibition->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Exhibition_Idle", L"..\\Resources\\Animation\\Shop\\shop_exhibition_idle.anim");
		pExhibition->GetAnimator()->AddAnimation(L"Exhibition_Idle", pAnimation);
		pExhibition->GetAnimator()->Play(L"Exhibition_Idle");

		pExhibition->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pExhibition, SCENE_TYPE::DUNGEON));
	}


	// Renew Shop Item List!
	
}

void Dungeon_Shop::Exit()
{
	Dungeon::Exit();
}
