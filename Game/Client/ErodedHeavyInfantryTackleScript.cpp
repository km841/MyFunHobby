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
#include "ObjectReturnToPoolEvent.h"
#include "CollisionManager.h"
#include "Clock.h"
#include "ComponentObject.h"
#include "SoundSource.h"

ErodedHeavyInfantryTackleScript::ErodedHeavyInfantryTackleScript()
	: m_tDamageTick(0.5f)
	, m_bTackleBeginFlag(false)
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

	if (MONSTER_STATE::TACKLE_LOOP == pMonster.lock()->GetMonsterState() ||
		MONSTER_STATE::RAGE_TACKLE_LOOP == pMonster.lock()->GetMonsterState())
	{
		if (!m_bTackleBeginFlag)
		{
			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Hardmode_Chapter3_Heavy_Tackle_Impact", L"..\\Resources\\Sound\\Hardmode_Chapter3_Heavy_Tackle_Impact.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
			m_bTackleBeginFlag = true;
		}

		uint8 iDirection = static_cast<uint8>(m_pFlashAura.lock()->GetDirection());
		m_pFlashAura.lock()->Enable();
		m_pFlashAura.lock()->GetTransform()->SetLocalPosition(Vec3(iDirection ? -20.f : 20.f, 0.f, -1.f));

		Vec3 vMonsterPos = pMonster.lock()->GetTransform()->GetPhysicalPosition();
		Vec3 vVolume = pMonster.lock()->GetTransform()->GetLocalScale();

		if (!m_tDamageTick.IsRunning())
			m_tDamageTick.Start();

		m_tDamageTick.Update(OBJECT_DELTA_TIME);

		if (m_tDamageTick.IsFinished())
		{
			GET_SINGLE(CollisionManager)->SetForceInPlayerAndTakeDamage(vMonsterPos, vVolume * 2.f, Vec3(iDirection ? -300.f : 300.f, 0.f, 0.f), 3.f);
			m_tDamageTick.Reset();
		}
	}

	else
	{
		m_pFlashAura.lock()->Disable();
	}

	if (MONSTER_STATE::RAGE_TACKLE_END == pMonster.lock()->GetMonsterState())
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(m_pFlashAura.lock(), SCENE_TYPE::DUNGEON));
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
