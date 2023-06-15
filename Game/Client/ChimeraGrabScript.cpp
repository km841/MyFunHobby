#include "pch.h"
#include "ChimeraGrabScript.h"
#include "Chimera.h"
#include "Clock.h"
#include "ObjectFactory.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"
#include "Animation.h"
#include "Animator.h"
#include "RigidBody.h"
#include "AnimationLocalEffect.h"
#include "ChimeraFallingObject.h"

ChimeraGrabScript::ChimeraGrabScript()
	: m_bCheckedBegin(false)
	, m_bCheckedSkill(false)
{
}

ChimeraGrabScript::~ChimeraGrabScript()
{
}

void ChimeraGrabScript::LateUpdate()
{
	weak_ptr<Chimera> pChimera = static_pointer_cast<Chimera>(GetGameObject());

	if (MONSTER_STATE::SKILL3_READY == pChimera.lock()->GetMonsterState())
	{
		if (!m_bCheckedBegin)
		{
			//CreateWarningSignAndAddedToScene();
			m_bCheckedBegin = true;
		}
	}
	else
	{
		m_bCheckedBegin = false;
	}

	if (MONSTER_STATE::SKILL3_END == pChimera.lock()->GetMonsterState())
	{
		if (!m_bCheckedSkill)
		{
			CreateFallingObjectAndAddedToScene();
			m_bCheckedSkill = true;
		}
	}
	else
	{
		m_bCheckedSkill = false;
	}
}

void ChimeraGrabScript::CreateWarningSignAndAddedToScene()
{
	// Warning Sign Animation

	shared_ptr<AnimationLocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.x -= 400.f;
	vPos.z -= 3.5f;

	pLocalEffect->AddComponent(make_shared<Animator>());
	pLocalEffect->GetTransform()->SetLocalPosition(vPos);

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"WarningSign", L"..\\Resources\\Animation\\MonsterCommon\\monster_common_attack_sign.anim");
	pLocalEffect->GetAnimator()->AddAnimation(L"WarningSign", pAnimation);
	pLocalEffect->GetAnimator()->Play(L"WarningSign", false);

	pLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
}

void ChimeraGrabScript::CreateFallingObjectAndAddedToScene()
{
	// 지정된 위치에 투하
	
	wstring szPathList[] =
	{
		L"..\\Resources\\Texture\\Sprites\\Chimera\\Image_Fall_Object01.png",
		L"..\\Resources\\Texture\\Sprites\\Chimera\\Image_Fall_Object02.png"
	};

	for (int32 i = 0; i < 2; ++i)
	{
		shared_ptr<ChimeraFallingObject> pFallingObject = 
			GET_SINGLE(ObjectFactory)->CreateObjectHasPhysical<ChimeraFallingObject>(L"Deferred", false, ACTOR_TYPE::MONSTER_DYNAMIC, GEOMETRY_TYPE::BOX, Vec3(50.f, 70.f, 30.f), MassProperties(), szPathList[i]);

		Vec3 vPos = GetTransform()->GetPhysicalPosition();
		vPos.x += i * 350.f - 850.f;
		vPos.y += 650.f;
		vPos.z += 3.5f;
		pFallingObject->GetTransform()->SetLocalPosition(vPos);

		pFallingObject->GetRigidBody()->SetLinearVelocityForDynamic(AXIS::Y, -300.f);

		pFallingObject->Awake();
		SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pFallingObject, eSceneType));
	}

	
}

