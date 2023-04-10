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

AbyssMeteorSkill::AbyssMeteorSkill()
	: SkulSkill(SKILL_TYPE::CHARGING, 5.f, 1.f)
{
	CreateConditionFunction();
	m_fMaxChargingTime = 5.f;
}

shared_ptr<AbyssMeteor> AbyssMeteorSkill::CreateAbyssMeteor()
{
	shared_ptr<AbyssMeteor> pAbyssMeteor = make_shared<AbyssMeteor>();

	pAbyssMeteor->AddComponent(make_shared<Transform>());
	pAbyssMeteor->AddComponent(make_shared<Physical>(ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 50.f, 1.f)));
	pAbyssMeteor->AddComponent(make_shared<RigidBody>(false));
	pAbyssMeteor->AddComponent(make_shared<Collider>());
	pAbyssMeteor->AddComponent(make_shared<DebugRenderer>());
	pAbyssMeteor->AddComponent(make_shared<Movement>());
	pAbyssMeteor->AddComponent(make_shared<Animator>());

	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->Load<Animation>(Conv::AddressToWstring(pAbyssMeteor.get()), L"..\\Resources\\Animation\\HighWarlock\\highwarlock_meteor.anim");
	pAbyssMeteor->GetAnimator()->AddAnimation(L"AbyssMeteor_Falling", pAnimation);
	pAbyssMeteor->GetAnimator()->Play(L"AbyssMeteor_Falling");

	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);
	pAbyssMeteor->AddComponent(pMeshRenderer);

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
	shared_ptr<AbyssMeteor> pAbyssMeteor = CreateAbyssMeteor();

	Vec3 vPlayerPos = Conv::PxVec3ToVec3(m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPxTransform().p);
	vPlayerPos.y += 1300.f;
	vPlayerPos.z -= 10.f;

	pAbyssMeteor->GetTransform()->SetLocalPosition(vPlayerPos);
	pAbyssMeteor->GetRigidBody()->SetVelocity(AXIS::Y, -100.f);


	pAbyssMeteor->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pAbyssMeteor, eSceneType));
}

void AbyssMeteorSkill::Exit()
{
}
