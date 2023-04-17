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

LittleBoneAttack::LittleBoneAttack(shared_ptr<Skul> pSkul)
	: SkulAttack(pSkul)
{
}

LittleBoneAttack::~LittleBoneAttack()
{
}

void LittleBoneAttack::Update()
{
	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	uint8 iOrder = static_cast<uint8>(m_eActiveAttackOrder);
	float fProgress = m_arrAttackInfo[iEnum][iOrder].pAnimation->GetAnimationProgress();
	if (IS_DOWN(KEY_TYPE::X) && fProgress > 0.75f && iOrder < m_iMaxCount - 1)
	{
		m_eActiveAttackOrder = static_cast<ATTACK_ORDER>(iOrder + 1);
		m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
	}

	// 한 프레임에 여러 번 호출되서 그런 것
	if (m_arrAttackInfo[iEnum][iOrder].pAnimation->IsHitFrame())
	{
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
	// RegisterAnimation
	shared_ptr<AnimationGlobalEffect> pHitEffect = AnimationGlobalEffect::Get();
	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"LittleBone_Hit", L"..\\Resources\\Animation\\LittleBone\\littlebone_hit.anim");

	vMonsterPos.z -= 1.0f;

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

	pHitEffect->AddComponent(make_shared<Transform>());
	pHitEffect->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRandomRadian));
	pHitEffect->GetTransform()->SetLocalPosition(vMonsterPos);

	shared_ptr<MeshRenderer> pMeshRenderer = make_shared<MeshRenderer>();
	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
	shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->LoadRectMesh();

	pMeshRenderer->SetMaterial(pMaterial);
	pMeshRenderer->SetMesh(pMesh);

	pHitEffect->AddComponent(pMeshRenderer);
	pHitEffect->AddComponent(make_shared<Animator>());

	pHitEffect->GetAnimator()->AddAnimation(L"LittleBone_Hit", pAnimation);
	pHitEffect->Awake();

	pHitEffect->GetAnimator()->Play(L"LittleBone_Hit", false);
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHitEffect, eSceneType));
}
