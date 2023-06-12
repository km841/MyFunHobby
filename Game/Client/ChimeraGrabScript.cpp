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
			CreateWarningSignAndAddedToScene();
			m_bCheckedBegin = true;
		}
	}
	else
	{
		m_bCheckedBegin = false;
	}

	if (MONSTER_STATE::SKILL3 == pChimera.lock()->GetMonsterState())
	{
		if (!m_bCheckedSkill)
		{
			CreateFallingObjectAndAddedToScene();
			m_bCheckedBegin = true;
		}
	}
	else
	{
		m_bCheckedBegin = false;
	}
}

void ChimeraGrabScript::CreateWarningSignAndAddedToScene()
{
	// Warning Sign Animation

	shared_ptr<AnimationLocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationLocalEffect>(L"Forward");

	Vec3 vPos = GetTransform()->GetPhysicalPosition();
	vPos.z -= 0.5f;
	vPos.y += 150.f;

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
}
