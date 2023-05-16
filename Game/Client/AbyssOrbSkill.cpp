#include "pch.h"
#include "AbyssOrbSkill.h"
#include "AbyssOrb.h"
#include "ObjectFactory.h"
#include "Animator.h"
#include "Animation.h"
#include "Movement.h"
#include "Skul.h"
#include "Player.h"


AbyssOrbSkill::AbyssOrbSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
	m_fMaxChargingTime = 5.f;
}

shared_ptr<AbyssOrb> AbyssOrbSkill::CreateAbyssOrb()
{
	shared_ptr<AbyssOrb> pAbyssOrb = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<AbyssOrb>(L"Forward", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(100.f, 100.f, 1.f));
	pAbyssOrb->AddComponent(make_shared<Animator>());
	pAbyssOrb->AddComponent(make_shared<Movement>());

	// AbyssOrb Repeat
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"AbyssOrb_Repeat", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_abyssorb_repeat.anim");
		pAbyssOrb->GetAnimator()->AddAnimation(L"AbyssOrb_Repeat", pAnimation);
	}

	// AbyssOrb Completed
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"AbyssOrb_Completed", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_abyssorb_completed.anim");
		pAbyssOrb->GetAnimator()->AddAnimation(L"AbyssOrb_Completed", pAnimation);
	}

	// AbyssOrb Despawn
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"AbyssOrb_Despawn", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_abyssorb_despawn.anim");
		pAbyssOrb->GetAnimator()->AddAnimation(L"AbyssOrb_Despawn", pAnimation);
	}

	pAbyssOrb->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));
	pAbyssOrb->GetAnimator()->Play(L"AbyssOrb_Repeat");
	return pAbyssOrb;
}

void AbyssOrbSkill::Update()
{
	SkulSkill::Update();
}

void AbyssOrbSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void AbyssOrbSkill::Enter()
{
	// Create Orb!
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	shared_ptr<AbyssOrb> pAbyssOrb = CreateAbyssOrb();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPxTransform().p);
	vPlayerPos.z -= 0.5f;

	uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());

	pAbyssOrb->GetTransform()->SetLocalPosition(vPlayerPos);
	pAbyssOrb->GetRigidBody()->SetVelocity(AXIS::X, iDirection ? -100.f : 100.f);

	pAbyssOrb->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAbyssOrb, eSceneType));
}

void AbyssOrbSkill::Exit()
{
}
