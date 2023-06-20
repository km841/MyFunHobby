#include "pch.h"
#include "AbyssMeteorSkill.h"
#include "GameObject.h"
#include "AbyssMeteor.h"
#include "IncompletedAbyssMeteor.h"
#include "Scene.h"
#include "Scenes.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "RigidBody.h"
#include "Transform.h"
#include "Physical.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Movement.h"
#include "DebugRenderer.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Skul.h"
#include "Player.h"
#include "Light.h"
#include "ObjectFactory.h"

AbyssMeteorSkill::AbyssMeteorSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
{
	CreateConditionFunction();
	m_fMaxChargingTime = 2.f;
}

shared_ptr<AbyssMeteor> AbyssMeteorSkill::CreateAbyssMeteor(const Vec3& vPos)
{
	shared_ptr<AbyssMeteor> pAbyssMeteor = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<AbyssMeteor>(L"Forward", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(100.f, 100.f, 1.f), MassProperties(), L"", vPos);
	pAbyssMeteor->AddComponent(make_shared<Animator>());
	pAbyssMeteor->AddComponent(make_shared<Movement>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(Conv::AddressToWstring(pAbyssMeteor.get()), L"..\\Resources\\Animation\\HighWarlock\\highwarlock_meteor.anim");
	pAbyssMeteor->GetTransform()->SetGlobalOffset(Vec2(0.f, 450.f));
	pAbyssMeteor->GetAnimator()->AddAnimation(L"AbyssMeteor_Falling", pAnimation);
	pAbyssMeteor->GetAnimator()->Play(L"AbyssMeteor_Falling");
	return pAbyssMeteor;
}

shared_ptr<IncompletedAbyssMeteor> AbyssMeteorSkill::CreateIncompletedAbyssMeteor(const Vec3& vPos)
{
	shared_ptr<IncompletedAbyssMeteor> pIncompletedMeteor = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<IncompletedAbyssMeteor>(L"Forward", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 1.f), MassProperties(), L"", vPos);
	pIncompletedMeteor->AddComponent(make_shared<Animator>());
	pIncompletedMeteor->AddComponent(make_shared<Movement>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(Conv::AddressToWstring(pIncompletedMeteor.get()), L"..\\Resources\\Animation\\HighWarlock\\highwarlock_meteor_incompleted.anim");
	pIncompletedMeteor->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));
	pIncompletedMeteor->GetAnimator()->AddAnimation(L"Incompleted_AbyssMeteor_Falling", pAnimation);
	pIncompletedMeteor->GetAnimator()->Play(L"Incompleted_AbyssMeteor_Falling");
	return pIncompletedMeteor;
}

void AbyssMeteorSkill::CreateFullChargingMeteor(const Vec3& vPos)
{
	shared_ptr<AbyssMeteor> pAbyssMeteor = CreateAbyssMeteor(vPos);
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPxTransform().p);
	vPlayerPos.y += 1000.f;
	vPlayerPos.z -= 0.5f;

	pAbyssMeteor->GetTransform()->SetLocalPosition(vPlayerPos);
	pAbyssMeteor->GetRigidBody()->SetVelocity(AXIS::Y, -100.f);

	pAbyssMeteor->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAbyssMeteor, eSceneType));
}

void AbyssMeteorSkill::CreateInsufficientMeteor(const Vec3& vPos)
{
	shared_ptr<IncompletedAbyssMeteor> pAbyssMeteor = CreateIncompletedAbyssMeteor(vPos);
	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPxTransform().p);
	vPlayerPos.y += 1000.f;
	vPlayerPos.x -= 1000.f;
	vPlayerPos.z -= 0.5f;

	pAbyssMeteor->GetTransform()->SetLocalPosition(vPlayerPos);
	pAbyssMeteor->GetRigidBody()->SetVelocity(Vec3(150.f, -200.f, 0.f));
	pAbyssMeteor->Awake();
	
	auto transform = pAbyssMeteor->GetPhysical()->GetActor<PxRigidDynamic>()->getGlobalPose();
	PxQuat rotation(PxPi / 4, PxVec3(0.f, 0.f, -1.f));
	PxTransform rotatedTransform = PxTransform(transform.p, rotation);
	pAbyssMeteor->GetPhysical()->GetActor<PxRigidDynamic>()->setGlobalPose(rotatedTransform);
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAbyssMeteor, eSceneType));
}

void AbyssMeteorSkill::Update()
{
	SkulSkill::Update();
}

void AbyssMeteorSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void AbyssMeteorSkill::Enter()
{
	m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(AXIS::X, 0.f);
	Vec3 vPlayerPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
	// Progress 양에 따라 다른 스킬 적용
	// Meteor에는 현재 플레이어 주변 위치를 기록해둔 뒤 반경 n만큼의 타일에 떨어져야만 폭발하도록 한다.

	if (m_fChargingProgress > 0.99f)
	{
		CreateFullChargingMeteor(vPlayerPos);
	}
	else
	{
		CreateInsufficientMeteor(vPlayerPos);
	}

}

void AbyssMeteorSkill::Exit()
{
}
