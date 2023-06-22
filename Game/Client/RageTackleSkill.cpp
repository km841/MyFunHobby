#include "pch.h"
#include "RageTackleSkill.h"
#include "Input.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "Skul.h"
#include "Player.h"
#include "LocalEffect.h"
#include "ObjectFactory.h"
#include "ObjectReturnToPoolEvent.h"
#include "RageTackleSlashEffect.h"
#include "Clock.h"
#include "PlayerState.h"

RageTackleSkill::RageTackleSkill(const SkillInfo& skillInfo)
	: SkulSkill(skillInfo)
	, m_fDepthValue(0.f)
	, m_tSlashTick(0.1f)
{
	CreateConditionFunction();
}

void RageTackleSkill::Update()
{
	SkulSkill::Update();
	// 스킬 시전 중 공격 키가 눌리면 돌격하며 공격 애니메이션 + 슬래쉬 + 플래쉬

	if (m_pSkul.lock()->GetPlayer().lock()->GetPlayerState().lock()->CheckGrounded())
	{
		m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->RemoveGravity();
		m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->SetVelocity(AXIS::Y, 0.f);
	}
	else
	{
		m_pSkul.lock()->GetPlayer().lock()->GetRigidBody()->ApplyGravity();
	}


	if (IS_UP(KEY_TYPE::S))
	{
		// 종료
		m_tDuration.SetProgress(0.9f);
		m_pFlashEffect.lock()->Disable();
	}
	else
	{
		m_pSkul.lock()->GetPlayer().lock()->GetActiveSkul()->PlayAnimation(PLAYER_STATE::DASH);
		m_pFlashEffect.lock()->Enable();
		
		if (!m_tSlashTick.IsRunning())
		{
			m_tSlashTick.Start();
		}
		else
		{
			m_tSlashTick.Update(WORLD_DELTA_TIME);
			if (m_tSlashTick.IsFinished())
			{
				GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(0.f, 500.f, 0.f));
				GET_SINGLE(Scenes)->GetActiveScene()->ShakeCameraAxis(0.05f, Vec3(500.f, 0.f, 0.f));
				CreateSlashEffectAndAddedToScene();
				m_tSlashTick.Reset();
			}
		}
		
		uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());
		m_pSkul.lock()->GetPlayer().lock()->GetStatus()->fSpeed = 700.f;
	}
}

void RageTackleSkill::CreateConditionFunction()
{
	m_fnCondition = [](weak_ptr<GameObject> pGameObject)
	{
		return true;
	};
}

void RageTackleSkill::Enter()
{
	CreateFlashEffectAndAddedToScene();
	m_pSkul.lock()->GetPlayer().lock()->GetStatus()->fSpeed = 1000.f;

	m_tSlashTick.SetEndTime(m_pSkul.lock()->GetEnumIndex() ? 0.1f : 0.3f);
}

void RageTackleSkill::Exit()
{
	m_pSkul.lock()->GetPlayer().lock()->GetStatus()->fSpeed = 400.f;
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(m_pFlashEffect.lock(), eSceneType));
	m_fDepthValue = 0.f;
	m_tSlashTick.Reset();
}

void RageTackleSkill::CreateSlashEffectAndAddedToScene()
{
	// 클래스를 만들어서 animation local effect로 처리
	shared_ptr<RageTackleSlashEffect> pSlashEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<RageTackleSlashEffect>(L"Forward");
	pSlashEffect->GetTransform()->SetParent(m_pSkul.lock()->GetTransform());

	uint8 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());
	pSlashEffect->GetTransform()->SetLocalPosition(Vec3(iDirection ? -20.f : 20.f, 20.f, -m_fDepthValue));
	m_fDepthValue++;
	pSlashEffect->GetTransform()->SetGlobalOffset(Vec2(0.f, 0.f));

	pSlashEffect->AddComponent(make_shared<Animator>());
	//pSlashEffect->AddComponent(make_shared<ObjectAttackAtHitFrameScript>(pSlashEffect, DAMAGE_TYPE::FROM_PLAYER_MAGIC, static_cast<float>(RANDOM(2, 5))));

	wstring szRandomAnim = {};
	int32 iRandomAlpha = RANDOM('a', 'e');
	pSlashEffect->SetSlashKind(iRandomAlpha);
	szRandomAnim.push_back(iRandomAlpha);
	szRandomAnim += L".anim";

	// Tackle Slash
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"RageTackle_Slash", L"..\\Resources\\Animation\\DevilBerserker\\berserker_rage_tackle_slash_" + szRandomAnim);
		pSlashEffect->GetAnimator()->AddAnimation(L"RageTackle_Slash", pAnimation);

		pAnimation->SetHitFrame(1);
	}

	pSlashEffect->GetAnimator()->Play(L"RageTackle_Slash", false);

	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pSlashEffect, eSceneType));
}

void RageTackleSkill::CreateFlashEffectAndAddedToScene()
{
	shared_ptr<LocalEffect> pLocalEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<LocalEffect>(L"Forward");
	pLocalEffect->GetTransform()->SetParent(m_pSkul.lock()->GetTransform());
	pLocalEffect->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -1.f));
	pLocalEffect->AddComponent(make_shared<Animator>());
	// Tackle Effect
	{
		shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"DevilBerserker_TackleEffect", L"..\\Resources\\Animation\\DevilBerserker\\berserker_tackle_flash.anim");
		pLocalEffect->GetAnimator()->AddAnimation(L"DevilBerserker_TackleEffect", pAnimation);
		pLocalEffect->GetAnimator()->Play(L"DevilBerserker_TackleEffect");
	}

	pLocalEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pLocalEffect, eSceneType));
	m_pFlashEffect.reset();
	m_pFlashEffect = pLocalEffect;
}
