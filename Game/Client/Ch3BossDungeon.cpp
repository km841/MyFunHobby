#include "pch.h"
#include "Ch3BossDungeon.h"
#include "MadScientist.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Animator.h"
#include "Animation.h"

Ch3BossDungeon::Ch3BossDungeon(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::STAGE_BOSS, szMapPath, szScriptPath)
{
}

Ch3BossDungeon::~Ch3BossDungeon()
{
}

void Ch3BossDungeon::Awake()
{
	Dungeon::Awake();
}

void Ch3BossDungeon::Start()
{
	Dungeon::Start();
}

void Ch3BossDungeon::Update()
{
	Dungeon::Update();
}

void Ch3BossDungeon::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Ch3BossDungeon::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Ch3BossDungeon::Enter()
{
	Dungeon::Enter();

	// 과학자 소환
	{
		shared_ptr<MadScientist> pMadScientist = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MadScientist>(L"Forward");
		pMadScientist->SetDirection(DIRECTION::LEFT);
		pMadScientist->GetTransform()->SetLocalPosition(Vec3(1056.f, 265.f, 101.f));

		pMadScientist->AddComponent(make_shared<Animator>());
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Idle", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_idle.anim");
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Idle", pAnimation);
		pMadScientist->GetAnimator()->Play(L"MadScientist_Idle");

		pMadScientist->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMadScientist, SCENE_TYPE::DUNGEON));
	}

	// 과학자 내부적으로 카운트를 보유하고 해당 카운트를 통해 애니메이션 변경
	// 카운트는 플레이어가 대화를 스킵할 떄나 대화가 자동으로 넘어갈 때 올라간다
}

void Ch3BossDungeon::Exit()
{
	Dungeon::Exit();
}
