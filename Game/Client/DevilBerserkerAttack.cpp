#include "pch.h"
#include "DevilBerserkerAttack.h"
#include "Physical.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Collider.h"
#include "DebugRenderer.h"
#include "Movement.h"
#include "Mesh.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Resources.h"
#include "Scenes.h"
#include "Scene.h"
#include "Player.h"
#include "GlobalEffect.h"
#include "ParticleSystem.h"
#include "ObjectFactory.h"
#include "Skul.h"
#include "Input.h"
#include "AnimationGlobalEffect.h"
#include "Animator.h"

DevilBerserkerAttack::DevilBerserkerAttack(shared_ptr<Skul> pSkul)
	: SkulAttack(pSkul)
{
	m_fDamage = 3.f;
}

DevilBerserkerAttack::~DevilBerserkerAttack()
{
}

void DevilBerserkerAttack::Update()
{
	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	uint8 iOrder = static_cast<uint8>(m_eActiveAttackOrder);
	float fProgress = m_arrAttackInfo[iEnum][iOrder].pAnimation->GetAnimationProgress();
	if (IS_PRESS(KEY_TYPE::X) && fProgress > 0.75f && iOrder < m_iMaxCount - 1)
	{
		m_eActiveAttackOrder = static_cast<ATTACK_ORDER>(iOrder + 1);
		m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
	}

	if (m_arrAttackInfo[iEnum][iOrder].pAnimation->IsHitFrame())
	{
		m_pSkul.lock()->GetPlayer().lock()->ActiveItemWhenHitTiming();

		HitMonstersInAttackRange();
		m_arrAttackInfo[iEnum][iOrder].pAnimation->CheckToHitFrame();
	}
}

void DevilBerserkerAttack::Enter()
{
	m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
}

void DevilBerserkerAttack::Exit()
{
	m_eActiveAttackOrder = ATTACK_ORDER::ATTACK_A;
}

void DevilBerserkerAttack::CreateHitEffectAndAddedScene(Vec3 vMonsterPos)
{
	shared_ptr<AnimationGlobalEffect> pHitEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationGlobalEffect>(L"Forward");

	int32 iRandomX = RANDOM(50, 100);
	int32 iRandomY = RANDOM(0, 30);

	int32 iRandomDegree = RANDOM(-30, 30);
	float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;

	DIRECTION eDirection = m_pSkul.lock()->GetDirection();
	switch (eDirection)
	{
	case DIRECTION::RIGHT:
		pHitEffect->SetDirection(DIRECTION::LEFT);
		vMonsterPos.x -= iRandomX;
		vMonsterPos.y -= iRandomY;
		break;
	case DIRECTION::LEFT:
		pHitEffect->SetDirection(DIRECTION::RIGHT);
		vMonsterPos.x += iRandomX;
		vMonsterPos.y -= iRandomY;
		break;
	}

	vMonsterPos.z -= 1.0f;

	pHitEffect->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRandomRadian));
	pHitEffect->GetTransform()->SetLocalPosition(vMonsterPos);
	pHitEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"LittleBone_Hit", L"..\\Resources\\Animation\\LittleBone\\littlebone_hit.anim");
	pHitEffect->GetAnimator()->AddAnimation(L"LittleBone_Hit", pAnimation);
	pHitEffect->GetAnimator()->Play(L"LittleBone_Hit", false);

	pHitEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHitEffect, eSceneType));
}