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

	// ������ ��ȯ
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

	// ������ ���������� ī��Ʈ�� �����ϰ� �ش� ī��Ʈ�� ���� �ִϸ��̼� ����
	// ī��Ʈ�� �÷��̾ ��ȭ�� ��ŵ�� ���� ��ȭ�� �ڵ����� �Ѿ �� �ö󰣴�
}

void Ch3BossDungeon::Exit()
{
	Dungeon::Exit();
}
