#include "pch.h"
#include "ErodedHeavyInfantryTackleScript.h"
#include "Monster.h"
#include "LocalEffect.h"
#include "ObjectFactory.h"
#include "Animator.h"
#include "Animation.h"
#include "Transform.h"
#include "Scenes.h"
#include "Scene.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"

ErodedHeavyInfantryTackleScript::ErodedHeavyInfantryTackleScript()
{
}

ErodedHeavyInfantryTackleScript::~ErodedHeavyInfantryTackleScript()
{
}

void ErodedHeavyInfantryTackleScript::LateUpdate()
{
	if (!m_pFlashAura.lock())
		CreateFlashAuraAndAddedToScene();


	weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(GetGameObject());

	if (MONSTER_STATE::TACKLE_LOOP == pMonster.lock()->GetMonsterState())
	{
		uint8 iDirection = static_cast<uint8>(m_pFlashAura.lock()->GetDirection());
		m_pFlashAura.lock()->Enable();
		m_pFlashAura.lock()->GetTransform()->SetLocalPosition(Vec3(iDirection ? -20.f : 20.f, 0.f, -1.f));
	}

	else
	{
		m_pFlashAura.lock()->Disable();
	}
}

void ErodedHeavyInfantryTackleScript::CreateFlashAuraAndAddedToScene()
{
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<LocalEffect>(L"Forward");
	pLocalEffect->Disable();

	pLocalEffect->GetTransform()->SetParent(GetTransform());
	pLocalEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -1.f));

	pLocalEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"ErodedHeavyInfantry_Flash", L"..\\Resources\\Animation\\ErodedHeavyInfantry\\eroded_heavy_infantry_tackle_flash.anim");
	pLocalEffect->GetAnimator()->AddAnimation(L"ErodedHeavyInfantry_Flash", pAnimation);
	pLocalEffect->GetAnimator()->Play(L"ErodedHeavyInfantry_Flash");

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
	m_pFlashAura = pLocalEffect;
}
