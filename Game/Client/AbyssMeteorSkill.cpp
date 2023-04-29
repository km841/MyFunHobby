#include "pch.h"
#include "AbyssMeteorSkill.h"
#include "GameObject.h"
#include "AbyssMeteor.h"
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
	m_fMaxChargingTime = 5.f;
}

shared_ptr<AbyssMeteor> AbyssMeteorSkill::CreateAbyssMeteor()
{
	shared_ptr<AbyssMeteor> pAbyssMeteor = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<AbyssMeteor>(L"Forward", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(100.f, 100.f, 1.f));
	pAbyssMeteor->AddComponent(make_shared<Animator>());
	pAbyssMeteor->AddComponent(make_shared<Movement>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(Conv::AddressToWstring(pAbyssMeteor.get()), L"..\\Resources\\Animation\\HighWarlock\\highwarlock_meteor.anim");
	pAbyssMeteor->GetTransform()->SetGlobalOffset(Vec2(0.f, 450.f));
	pAbyssMeteor->GetAnimator()->AddAnimation(L"AbyssMeteor_Falling", pAnimation);
	pAbyssMeteor->GetAnimator()->Play(L"AbyssMeteor_Falling");
	return pAbyssMeteor;
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

	shared_ptr<AbyssMeteor> pAbyssMeteor = CreateAbyssMeteor();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPxTransform().p);
	vPlayerPos.y += 1000.f;
	vPlayerPos.z -= 0.5f;

	pAbyssMeteor->GetTransform()->SetLocalPosition(vPlayerPos);
	pAbyssMeteor->GetRigidBody()->SetVelocity(AXIS::Y, -100.f);

	pAbyssMeteor->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAbyssMeteor, eSceneType));
}

void AbyssMeteorSkill::Exit()
{
}
