#include "pch.h"
#include "AlchemistFlaskThrowScript.h"
#include "Alchemist.h"
#include "ObjectFactory.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"
#include "AlchemistFlask.h"
#include "Player.h"
#include "Engine.h"
#include "Animation.h"
#include "Animator.h"

AlchemistFlaskThrowScript::AlchemistFlaskThrowScript()
	: m_bThrowFlag(false)
	, m_fThrowPower(500.f)
{
}

AlchemistFlaskThrowScript::~AlchemistFlaskThrowScript()
{
}

void AlchemistFlaskThrowScript::LateUpdate()
{
	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(GetGameObject());
	if (MONSTER_STATE::ATTACK == pMonster.lock()->GetMonsterState())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			CreateFlaskAndAddedToScene();
			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}
	}
}

void AlchemistFlaskThrowScript::CreateFlaskAndAddedToScene()
{
	shared_ptr<AlchemistFlask> pFlask = GET_SINGLE(ObjectFactory)->CreateObjectHasPhysicalFromPool<AlchemistFlask>(L"Forward", false, ACTOR_TYPE::PROJECTILE_DYNAMIC, GEOMETRY_TYPE::SPHERE, Vec3(10.f, 10.f, 10.f), MassProperties(), L"..\\Resources\\Texture\\Sprites\\Alchemist\\Image_Alchemist_Flask.png");

	Vec3 vPlayerPos = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetTransform()->GetPhysicalPosition();
	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
	Vec3 vFlaskPos = vMyPos;
	vFlaskPos.z -= 1.f;
	pFlask->GetTransform()->SetLocalPosition(vFlaskPos);

	uint8 iDirection = static_cast<uint8>(GetGameObject()->GetDirection());
	Vec3 vDiff = vPlayerPos - vMyPos;
	float fRadian = atan2(vDiff.y, vDiff.x);
	float fDegree = fRadian * 180.f / XM_PI;

	float fPower = m_fThrowPower;

	if (fDegree > 15.f)
		fPower *= 2.f;

	if (fDegree < 0.f && fDegree > -90.f)
		fRadian += 30.f * XM_PI / 180.f;
	if (fDegree < -90.f && fDegree > -180.f)
		fRadian -= 30.f * XM_PI / 180.f;
		
	Vec3 vRightNormal = VEC3_RIGHT_NORMAL;
	Vec3 vRotatedNormal = Vec3(vRightNormal.x * cosf(fRadian) + vRightNormal.y * sinf(fRadian),
		vRightNormal.x * sinf(fRadian) - vRightNormal.y * cosf(fRadian), 0.f);

	pFlask->Awake();
	pFlask->GetRigidBody()->SetLinearVelocityForDynamic(Conv::Vec3ToPxVec3(vRotatedNormal * fPower));
	pFlask->GetRigidBody()->SetAngularVelocityForDynamic(Conv::Vec3ToPxVec3(Vec3(0.f, 0.f, 10.f)));

	pFlask->AddComponent(make_shared<Animator>());
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Flask_Despawn", L"..\\Resources\\Animation\\Alchemist\\alchemist_flask_despawn.anim");
	pFlask->GetAnimator()->AddAnimation(L"Flask_Despawn", pAnimation);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pFlask, eSceneType));
}
