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
#include "Player.h"
#include "Sequence.h"
#include "Selector.h"
#include "Movement.h"
#include "Light.h"

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
#include "IsPlayerNearCondition.h"
#include "SetDirectionTowardPlayerTask.h"
#include "SetVelocityForDynamicObjectTask.h"
#include "SetVelocityGoToPlayerPosTask.h"
#include "VelocityZeroForKinematicTask.h"

#include "VeteranHeroLandingScript.h"
#include "VeteranHeroFallSkillScript.h"

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

	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	GET_SINGLE(Scenes)->GetActiveScene()->GetDirLight().lock()->GetLight()->SetDiffuse(Vec3(1.f, 1.f, 1.f));

	// Veteran Hero
	shared_ptr<VeteranHero> pVeteranHero = nullptr;
	{
		pVeteranHero = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<VeteranHero>(L"Deferred", true, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::SPHERE, Vec3(50.f, 50.f, 1.f), MassProperties());
		pVeteranHero->AddComponent(make_shared<Animator>());
		pVeteranHero->AddComponent(make_shared<AI>());
		pVeteranHero->AddComponent(make_shared<Movement>());
		pVeteranHero->AddComponent(make_shared<VeteranHeroLandingScript>());
		pVeteranHero->AddComponent(make_shared<VeteranHeroFallSkillScript>());
		pVeteranHero->SetDirection(DIRECTION::LEFT);
		pVeteranHero->GetTransform()->SetGlobalOffset(Vec2(0.f, 10.f));

		pVeteranHero->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);

		shared_ptr<Selector> pRootNode = make_shared<Selector>();
		shared_ptr<Sequence> pIdleSequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingSequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingEndSequence = make_shared<Sequence>();
		shared_ptr<Sequence> pLandingThrowingSequence = make_shared<Sequence>();

		shared_ptr<Sequence> pFallSkillReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pFallSkillSequence = make_shared<Sequence>();

		shared_ptr<Sequence> pComboAReadySequence = make_shared<Sequence>();
		shared_ptr<Sequence> pComboASequence = make_shared<Sequence>();
		// �Ÿ� ����-> Upper -> Slash

		shared_ptr<Sequence> pComboBSequence = make_shared<Sequence>();
		// �Ÿ� ���� -> JumpAttack -> Landing

		shared_ptr<Sequence> pComboCSequence = make_shared<Sequence>();
		// �÷��̾� �������� Stinger -> Slash

		shared_ptr<Sequence> pComboDSequence = make_shared<Sequence>();
		// �־��� �� ��������

		shared_ptr<Sequence> pBarriorSequence = make_shared<Sequence>();
		// �ʹ� ������ �踮��

		shared_ptr<Sequence> pComboESequence = make_shared<Sequence>();
		// �޺� A�� �����ϳ� �˱� �߻�

		shared_ptr<Sequence> pEnergyAtkSequence = make_shared<Sequence>();
		// HP 50% �����϶� ���ʻ�� �ߵ�

		shared_ptr<Sequence> pStingerRushSequence = make_shared<Sequence>();
		// HP 25% ������ �� �ʻ�� �ߵ�


		
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

		pRootNode->AddChild(pIdleSequence);
		{
			pIdleSequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::IDLE));
			pIdleSequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_Idle"));
			pIdleSequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));
			pIdleSequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::ATTACK_A_READY));
			// Random State
		}

		pRootNode->AddChild(pComboAReadySequence);
		{
			pComboAReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::ATTACK_A_READY));
			pComboAReadySequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_UpperAttackReady", false));
			//pComboAReadySequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));

			// �Ÿ� ��� �� �б�
			{
				shared_ptr<Selector> pStateSelector = make_shared<Selector>();
				{
					shared_ptr<Sequence> pDistCheckSequence = make_shared<Sequence>();
					pDistCheckSequence->AddChild(make_shared<IsPlayerNearCondition>(pPlayer.lock(), pVeteranHero, 100.f));
					pDistCheckSequence->AddChild(make_shared<VelocityZeroForKinematicTask>(pVeteranHero));
					pDistCheckSequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::ATTACK_A));
					pStateSelector->AddChild(pDistCheckSequence);
				}
				pStateSelector->AddChild(make_shared<SetDirectionTowardPlayerTask>(pPlayer.lock(), pVeteranHero));
				pComboAReadySequence->AddChild(pStateSelector);
				pComboAReadySequence->AddChild(make_shared<SetVelocityGoToPlayerPosTask>(pPlayer.lock(), pVeteranHero, 1000.f));
				pComboAReadySequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_Dash", false));
			}
			// �÷��̾���� �Ÿ� ��� �� �뽬
		}

		pRootNode->AddChild(pComboASequence);
		{
			pComboASequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::ATTACK_A));
			pComboASequence->AddChild(make_shared<VelocityZeroForKinematicTask>(pVeteranHero));
			pComboASequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_UpperAttack", false));
			pComboASequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));
			pComboASequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::IDLE));
		}

		pRootNode->AddChild(pFallSkillReadySequence);
		{
			pFallSkillReadySequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::SKILL1_READY));
			pFallSkillReadySequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_Jump", false));
			pFallSkillReadySequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 1.f));
			pFallSkillReadySequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::SKILL1));
		}

		pRootNode->AddChild(pFallSkillSequence);
		{
			pFallSkillSequence->AddChild(make_shared<IsMonsterStateCondition>(pVeteranHero, MONSTER_STATE::SKILL1));
			pFallSkillSequence->AddChild(make_shared<RunAnimateTask>(pVeteranHero, L"VeteranHero_FallDown", false));
			pFallSkillSequence->AddChild(make_shared<TimerCondition>(pVeteranHero, 3.f));
			//pFallSkillSequence->AddChild(make_shared<ChangeMonsterStateTask>(pVeteranHero, MONSTER_STATE::IDLE));
		}


		pVeteranHero->GetAI()->SetBehaviorRootNode(pRootNode);

		shared_ptr<Animation> pLandingReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingReady", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_ready.anim");
		shared_ptr<Animation> pLandingAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_Landing", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing.anim");
		shared_ptr<Animation> pLandingEndAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingEnd", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_end.anim");
		shared_ptr<Animation> pLandingThrowingAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_LandingThrowing", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_landing_throwing.anim");

		shared_ptr<Animation> pIdleAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_Idle", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_idle.anim");
		shared_ptr<Animation> pJumpAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_Jump", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_jump.anim");
		shared_ptr<Animation> pFallSkillAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_FallDown", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_e_landing.anim");
		
		shared_ptr<Animation> pBackDashAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_BackDash", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_back_dash.anim");
		shared_ptr<Animation> pDashAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_Dash", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_dash.anim");
		
		shared_ptr<Animation> pUpperAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_UpperAttack", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_a.anim");
		shared_ptr<Animation> pUpperAttackReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_UpperAttackReady", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_a_ready.anim");
		
		shared_ptr<Animation> pSlashAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_SlashAttack", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_b.anim");
		shared_ptr<Animation> pSlashAttackReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_SlashAttackReady", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_b_ready.anim");
		
		shared_ptr<Animation> pEnergyBallAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_EnergyBallAttack", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_c.anim");

		shared_ptr<Animation> pJumpAttackAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_JumpAttack", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_d.anim");
		shared_ptr<Animation> pJumpAttackReadyAnimation = GET_SINGLE(Resources)->LoadAnimation(L"VeteranHero_JumpAttackReady", L"..\\Resources\\Animation\\VeteranHero\\veteran_hero_attack_d_ready.anim");


		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingReady", pLandingReadyAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_Landing", pLandingAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingEnd", pLandingEndAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_LandingThrowing", pLandingThrowingAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_Idle", pIdleAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_Jump", pJumpAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_FallDown", pFallSkillAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_BackDash", pBackDashAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_Dash", pDashAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_UpperAttack", pUpperAttackAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_UpperAttackReady", pUpperAttackReadyAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_SlashAttack", pSlashAttackAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_SlashAttackReady", pSlashAttackReadyAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_EnergyBallAttack", pEnergyBallAttackAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_JumpAttack", pJumpAttackAnimation);
		pVeteranHero->GetAnimator()->AddAnimation(L"VeteranHero_JumpAttackReady", pJumpAttackReadyAnimation);
		pVeteranHero->GetRigidBody()->RemoveGravity();;

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
	AddEvent(make_shared<CameraFixedEvent>(pAlwaysTrueCondition, Vec3::Zero));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� ������!", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pVeteranHero, MONSTER_STATE::LANDING_READY));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���̷��� ������ ������� ���ٴ�! ��ħ ���� ȥ���� �� ������\n�����̾�. �������� ���� �������� ������ �� �ְھ�.", 3.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"ù ���迡�� ���� ���̷��� �� �������� �й��ߴٴ� �ҹ��� ������,\n�ƹ��� �� ���������� �ʴ���... �׵��� ���� ������ ����\n���ε��� �غ��ߴµ� ���̾�.", 3.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"��ġ������ �������̾���.", 1.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� �� �й�������? ������ �����غþ�. ������ �� �ϳ���.", 2.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"�� ����̶���?", 1.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"�װ� �ƴϸ� ���� �й��� ������ ���ݾ�? ������ ���̷��� ������ ����\n������ �̰ܸ��� ������ �ϴٴ�.", 3.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	//AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"���� ������ ����� �÷Ȱڴ�. �� �̻� ������ �ʰھ�.", 2.f));
	//AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pVeteranHero, MONSTER_STATE::LANDING_END));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"�߽� ���", L"������ ���� ���� �غ�� �Ǿ���?", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(pAlwaysTrueCondition, PLAYER_STATE::IDLE));
	AddEvent(make_shared<EnablePlayerHUDEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<PlayDungeonEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<MonsterChangeStateDungeonEvent>(pAlwaysTrueCondition, pVeteranHero, MONSTER_STATE::SKILL1_READY));
	
}

void Ch3ViceBossDungeon::Exit()
{
	Dungeon::Exit();
}