#include "pch.h"
#include "Ch3ViceBossDungeon.h"
#include "Resources.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Engine.h"
#include "ObjectAddedToSceneEvent.h"
#include "Scene.h"
#include "Scenes.h"
#include "Animator.h"
#include "Animation.h"
#include "PlayerChangeStateEvent.h"
#include "EventManager.h"
#include "Clock.h"
#include "PlayerWalkEvent.h"
#include "PlayerChangeStateDungeonEvent.h"
#include "IfAlwaysTrue.h"
#include "IfFinishedTimer.h"
#include "ObjectDisableEvent.h"
#include "ObjectEnableEvent.h"
#include "ActiveDialogueEvent.h"
#include "InterfaceManager.h"
#include "UI.h"
#include "DisablePlayerHUDEvent.h"
#include "EnablePlayerHUDEvent.h"
#include "NothingEvent.h"
#include "ChangeAnimationEvent.h"
#include "ChangeObjectPosEvent.h"
#include "AwakenChimeraEvent.h"
#include "MonsterChangeStateDungeonEvent.h"
#include "AI.h"
#include "ComponentObject.h"
#include "Camera.h"
#include "PauseDungeonEvent.h"
#include "CameraFixedEvent.h"
#include "CameraMovingEvent.h"
#include "VeteranHero.h"
#include "IfPlayerPosXExceedsN.h"
#include "DisableCameraTrackingEvent.h"
#include "EnableCameraTrackingEvent.h"

#include "Sequence.h"
#include "Selector.h"

#include "TimerCondition.h"
#include "IsMonsterStateCondition.h"
#include "ChangeMonsterStateTask.h"
#include "RunAnimateTask.h"
#include "AddSpineAnimationTask.h"
#include "AnimationClearTask.h"
#include "CameraFixedEvent.h"
#include "CameraUnfixEvent.h"
#include "PauseDungeonEvent.h"
#include "PlayDungeonEvent.h"
#include "EnableChapterBossHPBarEvent.h"
#include "ChangeChimeraRandomStateTask.h"
#include "EnableChapterBossHPBarTask.h"
#include "RemoveToSceneTask.h"

#include "VeteranHeroLandingScript.h"

Ch3ViceBossDungeon::Ch3ViceBossDungeon(const wstring& szMapPath, const wstring& szScriptPath)
	: Dungeon(DUNGEON_TYPE::VICE_BOSS, szMapPath, szScriptPath)
{
}

Ch3ViceBossDungeon::~Ch3ViceBossDungeon()
{
}

void Ch3ViceBossDungeon::Awake()
{
	Dungeon::Awake();
}

void Ch3ViceBossDungeon::Start()
{
	Dungeon::Start();
}

void Ch3ViceBossDungeon::Update()
{
	Dungeon::Update();
}

void Ch3ViceBossDungeon::LateUpdate()
{
	Dungeon::LateUpdate();
}

void Ch3ViceBossDungeon::FinalUpdate()
{
	Dungeon::FinalUpdate();
}

void Ch3ViceBossDungeon::Enter()
{
	Dungeon::Enter();

	// Veteran Hero
	shared_ptr<VeteranHero> pVeteranHero = nullptr;
	{
		pVeteranHero = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VeteranHero>(L"Forward", true, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties());
		pVeteranHero->AddComponent(make_shared<Animator>());
		pVeteranHero->AddComponent(make_shared<AI>());
		pVeteranHero->AddComponent(make_shared<VeteranHeroLandingScript>());
		pVeteranHero->SetDirection(DIRECTION::LEFT);

		shared_ptr<Selector> pRootNode = make_shared<Selector>();
		shared_ptr<Sequence> pLandingReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingSequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingEndSequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingThrowingSequence = make_shared<Sequence>();
		
		pRootNode->AddChild(pLandingReadySequence);
		{
			pLandingReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::LANDING_READY));
			pLandingReadySequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_LandingReady"));
			pLandingReadySequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));
			//pLandingReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::LANDING));
		}

		pRootNode->AddChild(pLandingEndSequence);
		{
			pLandingEndSequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::LANDING_END));
			pLandingEndSequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_LandingEnd", false));
			pLandingEndSequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));
			//pLandingReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::LANDING));
		}

		pVeteranHero->GetAI()->SetBehaviorRootNode(pRootNode);

		shared_ptr<Animation> pLandingReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingReady", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_ready.anim");
		shared_ptr<Animation> pLandingAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_Landing", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing.anim");
		shared_ptr<Animation> pLandingEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingEnd", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_end.anim");
		shared_ptr<Animation> pLandingThrowingAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingThrowing", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_throwing.anim");

		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingReady", pLandingReadyAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_Landing", pLandingAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingEnd", pLandingEndAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingThrowing", pLandingThrowingAnimation);
		pVeteranHero->GetPhysical()->GetActor<PxRigidDynamic>()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

		// Animations
		pVeteranHero->GetAnimator()->Play(L"VeteranHero_LandingThrowing", false);
		pVeteranHero->GetTransform()->SetLocalPosition(Vec3(1100.f, -142.f, 100.f));

		pVeteranHero->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pVeteranHero, SCENE_TYPE::DUNGEON));
	}

	shared_ptr<IfAlwaysTrue> pAlwaysTrueCondition = make_shared<IfAlwaysTrue>();
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(make_shared<IfPlayerPosXExceedsN>(-200.f), PLAYER_STATE::PAUSE_WALK));
	AddEvent(make_shared<PauseDungeonEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<DisablePlayerHUDEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<DisableCameraTrackingEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<CameraMovingEvent>(pAlwaysTrueCondition, Vec3(350.f, -300.f, 1.f), 1.5f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� ������!", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pVeteranHero, MONSTER_STATE::LANDING_READY));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���̷��� ������ ������� ���ٴ�! ��ħ ���� ȥ���� �� ������\n�����̾�. �������� ���� �������� ������ �� �ְھ�.", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"ù ���迡�� ���� ���̷��� �� �������� �й��ߴٴ� �ҹ��� ������,\n�ƹ��� �� ���������� �ʴ���... �׵��� ���� ������ ����\n���ε��� �غ��ߴµ� ���̾�.", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"��ġ������ �������̾���.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� �� �й�������? ������ �����غþ�. ������ �� �ϳ���.", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"�� ����̶���?", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"�װ� �ƴϸ� ���� �й��� ������ ���ݾ�? ������ ���̷��� ������ ����\n������ �̰ܸ��� ������ �ϴٴ�.", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� ������ ����� �÷Ȱڴ�. �� �̻� ������ �ʰھ�.", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pVeteranHero, MONSTER_STATE::LANDING_END));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"������ ���� ���� �غ�� �Ǿ���?", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(pAlwaysTrueCondition, PLAYER_STATE::IDLE));
	AddEvent(make_shared<EnablePlayerHUDEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<PlayDungeonEvent>(pAlwaysTrueCondition));
	//AddEvent(make_shared<CameraFixedEvent>(pAlwaysTrueCondition, Vec3(590.f, 355.f, 1.f)));
}

void Ch3ViceBossDungeon::Exit()
{
	Dungeon::Exit();
}
