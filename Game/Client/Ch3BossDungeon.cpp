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

	// Player State Change
	GET_SINGLE(Clock)->Pause();
	GET_SINGLE(EventManager)->AddEvent(make_unique<PlayerChangeStateEvent>(GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer(), PLAYER_STATE::PAUSE_IDLE));

	// ������ ��ȯ
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


	shared_ptr<IfAlwaysTrue> pAlwaysTrueCondition = make_shared<IfAlwaysTrue>();

	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(pAlwaysTrueCondition, PLAYER_STATE::PAUSE_WALK));
	AddEvent(make_shared<DisablePlayerHUDEvent>(pAlwaysTrueCondition));
	AddEvent(make_shared<PlayerWalkEvent>(pAlwaysTrueCondition, Vec3(300.f, 0.f, 0.f), 2.f));
	AddEvent(make_shared<PlayerChangeStateDungeonEvent>(make_shared<IfFinishedTimer>(2.f), PLAYER_STATE::PAUSE_IDLE));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"�� �� ������.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"��⸸ �ص� ġ������ ��ǰ�� �Ѱ����̾�.", 2.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"�ᱹ ������� �Ա���.", 1.5f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"�����忡�� �̾߱�� �� ���� �����.\n�ڱ� ���ϵ��� ��� �� �ųİ� ����ؼ� ������ �Ͷ߸�����.", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"�ʹ� ����� �� ���Ƽ� ���ʿ� �ִ� ������ ����־���.\n���� �� ������ �� �� ���Ҿ�. ���� ������ �ߴµ�,\n�̰����� �߶󳻴ϱ� �� �ƴ��� ������.", 4.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(6.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Laugh"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"������������", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Idle"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"����ü���� ������ ��� �ϵ��� ������ ���� ����ִ� �� ����. ���?\n������ ���յ� �� �������� ����? �񷯺��ҳ�? �󸮰ų� �ҿ� \n������ ���ҳ�? �༮���� ������ ���� �� ����Ͽ� ���� ���� ��ź�鵵 \n�־�ôµ�, ȿ���� �־���? �, ����־���?", 6.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(7.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_CrazyLaugh"));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"������������������������������������������������������������\n������������������������������������������������������������\n������������������������������������������������������������\n������������������������������������������������������������\n", 6.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(7.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Crazy"));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"..........................................................................................\n..........................................................................................\n..........................................................................................\n..........................................................................................\n", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Back", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"..........................................................................................\n..........................................................................................\n..........................................................................................\n..........................................................................................\n", 3.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(4.f)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"��̾��� �༮�̱���.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ObjectDisableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Stand", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(5.f)));
	AddEvent(make_shared<ObjectEnableEvent>(pAlwaysTrueCondition, GET_SINGLE(InterfaceManager)->Get(UI_TYPE::DIALOGUE)));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"���� ����ִ� �� �����ٰ�.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ChangeObjectPosEvent>(pAlwaysTrueCondition, pMadScientist, Vec3(990.f, 265.f, 101.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_First", false));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"������ ���� ����� ����ϸ� � ���� ����������.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(3.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_Second", false));
	AddEvent(make_shared<ActiveDialogueEvent>(pAlwaysTrueCondition, L"���� ��������", L"�� ��.", 1.f));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(1.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Attack_Third", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(0.3f)));
	AddEvent(make_shared<ChangeObjectPosEvent>(pAlwaysTrueCondition, pMadScientist, Vec3(960.f, 265.f, 101.f)));
	AddEvent(make_shared<ChangeAnimationEvent>(pAlwaysTrueCondition, pMadScientist, L"MadScientist_Dead", false));
	AddEvent(make_shared<NothingEvent>(make_shared<IfFinishedTimer>(2.f)));

	// Create Chimera
	{
		shared_ptr<Chimera> pChimera = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysical<Chimera>(L"Forward");
		pChimera->GetTransform()->SetLocalPosition(Vec3(300.f, 0.f, 100.f));
		pChimera->GetTransform()->SetLocalScale(Vec3(300.f, 300.f, 1.f));
		pChimera->Disable();
		pChimera->Awake();
		pChimera->PlayAnimation("animation");
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pChimera, SCENE_TYPE::DUNGEON));
	}
}

void Ch3BossDungeon::Exit()
{
	Dungeon::Exit();
}
