#include "pch.h"
#include "BoneHawlSkill.h"
#include "Player.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Skul.h"
#include "DevilBerserker.h"
#include "AnimationLocalEffect.h"
#include "ObjectFactory.h"
#include "Transform.h"
#include "Animator.h"
#include "Animation.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "CollisionManager.h"


BoneHawlSkill::BoneHawlSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
}

void BoneHawlSkill::Update()
{
	SkulSkill::Update();
}

void BoneHawlSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void BoneHawlSkill::Enter()
{
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(Vec3::Zero);
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->RemoveGravity();
	m_pSkul.lock()->GetPlayer().lock()->Pause();
}

void BoneHawlSkill::Exit()
{
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->ApplyGravity();
	m_pSkul.lock()->GetPlayer().lock()->Play();
	static_pointer_cast<DevilBerserker>(m_pSkul.lock())->Demonization();

	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(0.f, 2000.f, 0.f));
	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(2000.f, 0.f, 0.f));
	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(0.f, 2000.f, 0.f));
	GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.1f, Vec3(2000.f, 0.f, 0.f));
	CreateRoarEffectAndAddedToScene();

	Vec3 vMyPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
	GET_SINGLE(CollisionManager)->SetForceInLayer(LAYER_TYPE::PARTICLE, vMyPos, Vec3(2000.f, 2000.f, 0.f), Vec3(static_cast<float>(RANDOM(-1000, 1000)), 1000.f, 0.f));
	GET_SINGLE(CollisionManager)->SetForceInMonsterAndTakeDamage(vMyPos, Vec3(2000.f * 2.f, 2000.f * 2.f, 0.f), Vec3(static_cast<float>(RANDOM(-1000, 1000)), 1000.f, 0.f), static_cast<float>(RANDOM(50, 100)), DAMAGE_TYPE::FROM_PLAYER_MELEE);
}

void BoneHawlSkill::CreateRoarEffectAndAddedToScene()
{
	shared_ptr<AnimationLocalEffect> pRoar = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	Vec3 vPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
	vPos.z -= 1.f;

	pRoar->GetTransform()->SetLocalPosition(vPos);
	pRoar->AddComponent(make_shared<Animator>());
	// Chimera Roar
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DevilBerserker_Roar", L"..\\Resources\\Animation\\DevilBerserker\\berserker_demonization_roar.anim");
		pRoar->GetAnimator()->AddAnimation(L"DevilBerserker_Roar", pAnimation);
		pRoar->GetAnimator()->Play(L"DevilBerserker_Roar", false);
	}

	pRoar->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pRoar, eSceneType));
}
