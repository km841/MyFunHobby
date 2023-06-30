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
#include "Chimera.h"
#include "AwakenChimeraEvent.h"
#include "MonsterChangeStateDungeonEvent.h"
#include "AI.h"
#include "ComponentObject.h"
#include "Camera.h"

// Behavior Node
#include "TimerCondition.h"
#include "IsMonsterStateCondition.h"
#include "ChangeMonsterStateTask.h"
#include "RunSpineAnimateTask.h"
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
#include "PlayBGMEvent.h"
#include "StopBGMEvent.h"
#include "IfAllDeadMonsterInDungeon.h"
#include "RegisterSceneEvent.h"
#include "DisableChapterBossHPBarEvent.h"
#include "PlaySoundEvent.h"
#include "SceneChangeDungeonEvent.h"



#include "ChimeraVenomBallScript.h"
#include "ChimeraVenomFallScript.h"
#include "ChimeraGrabScript.h"
#include "ChimeraBreathScript.h"

#include "Selector.h"
#include "Sequence.h"

#include "SoundSource.h"

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
	SCENE_SOUND->StopBGM();
	// Player State Change

	GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer(), PLAYER_STATE::PAUSE_IDLE));

	// 과학자 소환
	shared_ptr<MadScientist> pMadScientist = nullptr;
	{
		pMadScientist = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<MadScientist>(L"Forward");
		pMadScientist->SetDirection(DIRECTION::LEFT);
		pMadScientist->GetTransform()->SetLocalPosition(Vec3(1056.f, 265.f, 101.f));

		pMadScientist->AddComponent(make_shared<Animator>());

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Idle", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_idle.anim");
		shared_ptr<Animation> pAttackFirstAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Attack_First", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_attack_first.anim");
		shared_ptr<Animation> pAttackSecondAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Attack_Second", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_attack_second.anim");
		shared_ptr<Animation> pAttackThirdAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Attack_Third", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_attack_third.anim");
		shared_ptr<Animation> pBackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Back", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_back.anim");
		shared_ptr<Animation> pCrazyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Crazy", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_crazy.anim");
		shared_ptr<Animation> pCrazyLaughAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_CrazyLaugh", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_crazylaugh.anim");
		shared_ptr<Animation> pDeadAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Dead", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_dead.anim");
		shared_ptr<Animation> pDisappointAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Disappoint", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_disappoint.anim");
		shared_ptr<Animation> pLaughAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Laugh", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_laugh.anim");
		shared_ptr<Animation> pStandAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Stand", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_stand.anim");
		shared_ptr<Animation> pWaitAnimation = GET_SINGLE(Resources)->LoadAnimation(L"MadScientist_Wait", L"..\\Resources\\Animation\\MadScientist\\mad_scientist_wait.anim");
		
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Idle", pIdleAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Attack_First", pAttackFirstAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Attack_Second", pAttackSecondAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Attack_Third", pAttackThirdAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Back", pBackAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Crazy", pCrazyAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_CrazyLaugh", pCrazyLaughAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Dead", pDeadAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Disappoint", pDisappointAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Laugh", pLaughAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Stand", pStandAnimation);
		pMadScientist->GetAnimator()->AddAnimation(L"MadScientist_Wait", pWaitAnimation);
		
		pMadScientist->GetAnimator()->Play(L"MadScientist_Idle");

		pMadScientist->Awake();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pMadScientist, SCENE_TYPE::DUNGEON));
	}

	// Create Chimera
	shared_ptr<Chimera> pChimera = nullptr;
	{
		pChimera = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<Chimera>(L"Deferred", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(200.f, 200.f, 1.f), MassProperties(), L"", pMadScientist);
		pChimera->GetTransform()->SetLocalPosition(Vec3(1000.f, 225.f, 103.f));
		pChimera->AddComponent(make_shared<AI>());
		pChimera->AddComponent(make_shared<DebugRenderer>());
		pChimera->AddComponent(make_shared<ChimeraVenomBallScript>());
		pChimera->AddComponent(make_shared<ChimeraVenomFallScript>());
		pChimera->AddComponent(make_shared<ChimeraGrabScript>());
		pChimera->AddComponent(make_shared<ChimeraBreathScript>());

		shared_ptr<Selector> pRootNode = make_shared<Selector>();
		shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();

		// Venom Ball Skill
		shared_ptr<Sequence> pSkill1ReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill1Sequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill1EndSequence = make_shared<Sequence>();

		// Venom Fall Skill
		shared_ptr<Sequence> pSkill2ReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill2Sequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill2EndSequence = make_shared<Sequence>();

		// Grab Skill
		shared_ptr<Sequence> pSkill3ReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill3Sequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill3EndSequence = make_shared<Sequence>();

		// Breath Skill
		shared_ptr<Sequence> pSkill4ReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill4Sequence = make_shared<Sequence>();
		shared_ptr<Sequence> pSkill4EndSequence = make_shared<Sequence>();

		// Dead
		shared_ptr<Sequence> pDeadSequence = make_shared<Sequence>();
		
		pRootNode->AddChild(pDeadSequence);
		{
			pDeadSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::DEAD));
			pDeadSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Dead", false));
			pDeadSequence->AddChild(make_shared<TimerCondition>(pChimera, 5.f));
			pDeadSequence->AddChild(make_shared<RemoveToSceneTask>(pChimera));
		}

		pRootNode->AddChild(pIdleSequence);
		{
			pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::IDLE));
			pIdleSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Idle"));
			pIdleSequence->AddChild(make_shared<TimerCondition>(pChimera, 2.f));
			pIdleSequence->AddChild(make_shared<ChangeChimeraRandomStateTask>(pChimera));
		}

		pRootNode->AddChild(pSkill1ReadySequence);
		{
			pSkill1ReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL1_READY));
			pSkill1ReadySequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Shot_Start", false));
			pSkill1ReadySequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
			pSkill1ReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL1));
		}

		// Venom Ball Skill
		pRootNode->AddChild(pSkill1Sequence);
		{
			pSkill1Sequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL1));
			pSkill1Sequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Shot", false));
			pSkill1Sequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
		}

		
		pRootNode->AddChild(pSkill1EndSequence);
		{
			pSkill1EndSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL1_END));
			pSkill1EndSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Shot_End", false));
			pSkill1EndSequence->AddChild(make_shared<TimerCondition>(pChimera, 0.5f));
			pSkill1EndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::IDLE));
		}

		// Venom Fall Skill
		pRootNode->AddChild(pSkill2ReadySequence);
		{
			pSkill2ReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL2_READY));
			pSkill2ReadySequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Roar_Start", false));
			pSkill2ReadySequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
			pSkill2ReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL2));
		}


		pRootNode->AddChild(pSkill2Sequence);
		{
			pSkill2Sequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL2));
			pSkill2Sequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Roar", false));
			pSkill2Sequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
			pSkill2Sequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL2_END));
		}


		pRootNode->AddChild(pSkill2EndSequence);
		{
			pSkill2EndSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL2_END));
			pSkill2EndSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Roar_Skill_Loop", true));
			pSkill2EndSequence->AddChild(make_shared<TimerCondition>(pChimera, 5.f));
			pSkill2EndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::IDLE));
		}

		// Grab Skill
		pRootNode->AddChild(pSkill3ReadySequence);
		{
			pSkill3ReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL3_READY));
			pSkill3ReadySequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Grab_Start", false));
			pSkill3ReadySequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
			pSkill3ReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL3));
		}


		pRootNode->AddChild(pSkill3Sequence);
		{
			pSkill3Sequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL3));
			pSkill3Sequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Grab_Back", false));
			pSkill3Sequence->AddChild(make_shared<TimerCondition>(pChimera, 2.f));
			pSkill3Sequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL3_END));
		}


		pRootNode->AddChild(pSkill3EndSequence);
		{
			pSkill3EndSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL3_END));
			pSkill3EndSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Grab_Smash", false));
			pSkill3EndSequence->AddChild(make_shared<TimerCondition>(pChimera, 1.f));
			pSkill3EndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL4_READY));
		}

		// Breath Skill
		pRootNode->AddChild(pSkill4ReadySequence);
		{
			pSkill4ReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL4_READY));
			pSkill4ReadySequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Grab_Loop"));
			pSkill4ReadySequence->AddChild(make_shared<TimerCondition>(pChimera, 2.f));
			pSkill4ReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL4));
		}


		pRootNode->AddChild(pSkill4Sequence);
		{
			pSkill4Sequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL4));
			pSkill4Sequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Breath", false));
			pSkill4Sequence->AddChild(make_shared<TimerCondition>(pChimera, 3.f));
			pSkill4Sequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::SKILL4_END));
		}


		pRootNode->AddChild(pSkill4EndSequence);
		{
			pSkill4EndSequence->AddChild(make_shared<IsMonsterStateCondition>(pChimera, MONSTER_STATE::SKILL4_END));
			pSkill4EndSequence->AddChild(make_shared<RunSpineAnimateTask>(pChimera, "Breath_End", false));
			pSkill4EndSequence->AddChild(make_shared<TimerCondition>(pChimera, 3.f));
			pSkill4EndSequence->AddChild(make_shared<ChangeMonsterStateTask>(pChimera, MONSTER_STATE::IDLE));
		}


		pChimera->GetAI()->SetBehaviorRootNode(pRootNode);

		pChimera->Awake();
		pChimera->Disable();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimera, SCENE_TYPE::DUNGEON));
	}

	shared_ptr<IfAlwaysTrue> pAlwaysTrueCondition = make_shared<IfAlwaysTrue>();
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(pAlwaysTrueCondition, PLAYER_STATE::PAUSE_WALK));
	AddEvent(make_shared<PauseDungeonEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<DisablePlayerHUDEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<PlayerWalkEvent>(pAlwaysTrueCondition, Vec3(300.f, 0.f, 0.f), 2.f));
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(make_shared<IfFinishedTimer>(2.f), PLAYER_STATE::PAUSE_IDLE));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<CameraFixedEvent>(pAlwaysTrueCondition, Vec3(590.f, 355.f, 1.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"발 밑 조심해.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"닿기만 해도 치명적인 약품이 한가득이야.", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"결국 여기까지 왔구나.", 1.5f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"기사단장에게 이야기는 다 전해 들었어.\n자기 부하들을 어떻게 한 거냐고 흥분해서 분통을 터뜨리더군.", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"너무 흥분한 것 같아서 저쪽에 있는 수조에 집어넣었어.\n열을 좀 식혀야 할 것 같았어. 조금 비좁긴 했는데,\n이곳저곳 잘라내니까 꽤 아늑해 보였어.", 4.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(6.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Laugh"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"하하하하하하", 1.f));
	AddEvent(make_shared<PlaySoundEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\DarkAlchemist_Laugh.wav"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Idle"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"실험체들을 가지고 노는 일들은 언제나 정말 재미있는 것 같아. 어땠어?\n마석과 결합된 네 동포들의 힘은? 찔러보았나? 얼리거나 불에 \n그을려 보았나? 녀석들이 언젠가 덤빌 걸 대비하여 몸에 작은 폭탄들도 \n넣어봤는데, 효과는 있었니? 어때, 재미있었지?", 6.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(7.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_CrazyLaugh"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"하하하하하하하하하하하하하하하하하하하하하하하하하하하하하하\n하하하하하하하하하하하하하하하하하하하하하하하하하하하하하하\n하하하하하하하하하하하하하하하하하하하하하하하하하하하하하하\n하하하하하하하하하하하하하하하하하하하하하하하하하하하하하하\n", 6.f));
	AddEvent(make_shared<PlaySoundEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\DarkAlchemist_CrazyLaugh.wav"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(7.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Crazy"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"..........................................................................................\n..........................................................................................\n..........................................................................................\n..........................................................................................\n", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Back", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"..........................................................................................\n..........................................................................................\n..........................................................................................\n..........................................................................................\n", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"재미없는 녀석이구나.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Stand", false));
	AddEvent(make_shared<PlaySoundEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\DarkAlchemist_Walk.wav"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(5.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"내가 재미있는 걸 보여줄게.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ChangeObjectPosEvent>(pAlwaysTrueCondition, pMadScientist, Vec3(990.f, 265.f, 101.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_First", false));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"마석의 힘을 제대로 사용하면 어떤 일이 벌어지는지.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_Second", false));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"검은 연구소장", L"잘 봐.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_Third", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(0.3f)));
	AddEvent(make_shared<ChangeObjectPosEvent>(pAlwaysTrueCondition, pMadScientist, Vec3(960.f, 265.f, 101.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Dead", false));
	AddEvent(make_shared<PlaySoundEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\DarkAlchemist_Down.wav"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	// HP Bar- 
	AddEvent(make_shared<PlayBGMEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\Chapter3_Boss.wav"));
	AddEvent(make_shared<EnableChapterBossHPBarEvent>(pAlwaysTrueCondition, STAGE_KIND::BLACK_LAB, pChimera));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<AwakenChimeraEvent>(make_shared<IfAlwaysTrue>(), pChimera));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(10.f)));
	AddEvent(make_shared<EnablePlayerHUDEvent>(pAlwaysTrueCondition));
	// Play Event- ok

	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(make_shared<IfFinishedTimer>(2.f), PLAYER_STATE::IDLE));
	AddEvent(make_shared<PlayDungeonEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pChimera, MONSTER_STATE::IDLE));
	AddEvent(make_shared<DisablePlayerHUDEvent>(make_shared<IfAllDeadMonsterInDungeon>()));
	AddEvent(make_shared<DisableChapterBossHPBarEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<StopBGMEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<PlaySoundEvent>(pAlwaysTrueCondition, L"..\\Resources\\Sound\\Hardmode_Cutscene_Ending_Normal.wav"));
	AddEvent(make_shared<RegisterSceneEvent>(pAlwaysTrueCondition, EVENT_TYPE::ACTIVATE_BROKENSCREEN, 5.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(5.1f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()));
	AddEvent(make_shared<SceneChangeDungeonEvent>(pAlwaysTrueCondition, SCENE_TYPE::ENDING));

}

void Ch3BossDungeon::Exit()
{
	Dungeon::Exit();
}
