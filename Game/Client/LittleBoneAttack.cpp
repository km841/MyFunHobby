#include "pch.h"
#include "LittleBoneAttack.h"
#include "LittleBone.h"
#include "Animation.h"
#include "Input.h"
#include "Resources.h"
#include "AnimationGlobalEffect.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Animator.h"
#include "Mesh.h"
#include "Scenes.h"
#include "Scene.h"
#include "ObjectAddedToSceneEvent.h"
#include "EventManager.h"
#include "Player.h"
#include "RigidBody.h"
#include "ObjectFactory.h"

LittleBoneAttack::LittleBoneAttack(shared_ptr<Skul> pSkul)
	: SkulAttack(pSkul)
{
	m_fDamage = 3.f;
}

LittleBoneAttack::~LittleBoneAttack()
{
}

void LittleBoneAttack::Update()
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

		LittleBoneStomp();
		HitMonstersInAttackRange();
		m_arrAttackInfo[iEnum][iOrder].pAnimation->CheckToHitFrame();
	}
}

void LittleBoneAttack::Enter()
{
	m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
}

void LittleBoneAttack::Exit()
{
	m_eActiveAttackOrder = ATTACK_ORDER::ATTACK_A;
}

void LittleBoneAttack::CreateHitEffectAndAddedScene(Vec3 vMonsterPos)
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

void LittleBoneAttack::LittleBoneStomp()
{
	if (m_pSkul.lock()->GetPlayer().lock()->DoesTileExistInDirection(m_pSkul.lock()->GetDirection(), 2.f))
	{
		Vec3 vMyPos = m_pSkul.lock()->GetPlayer().lock()->GetTransform()->GetPhysicalPosition();
		DIRECTION eDirection = m_pSkul.lock()->GetDirection();
		
		bool bChanged = false;
		switch (eDirection)
		{
		case DIRECTION::RIGHT:
			if (IS_PRESS(KEY_TYPE::RIGHT))
			{
				vMyPos.x += 30.f;
				bChanged = true;
			}
			break;
		case DIRECTION::LEFT:
			if (IS_PRESS(KEY_TYPE::LEFT))
			{
				vMyPos.x -= 30.f;
				bChanged = true;
			}
			break;
		}

		if (bChanged)
			m_pSkul.lock()->GetPlayer().lock()->GetTransform()->SetPhysicalPosition(vMyPos);
	}

}
