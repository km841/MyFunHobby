#include "pch.h"
#include "HighWarlockAttack.h"
#include "Skul.h"
#include "Animation.h"
#include "Input.h"
#include "HighWarlockBaseProjectile.h"
#include "ObjectFactory.h"
#include "EventManager.h"
#include "ObjectAddedToSceneEvent.h"
#include "Resources.h"
#include "Scenes.h"
#include "Scene.h"
#include "Animator.h"
#include "Player.h"

HighWarlockAttack::HighWarlockAttack(shared_ptr<Skul> pSkul)
	: SkulAttack(pSkul)
	, m_fBaseProjectileSpeed(500.f)
{
}

HighWarlockAttack::~HighWarlockAttack()
{
}

void HighWarlockAttack::Update()
{
	uint8 iEnum = m_pSkul.lock()->GetEnumIndex();
	uint8 iOrder = static_cast<uint8>(m_eActiveAttackOrder);
	float fProgress = m_arrAttackInfo[iEnum][iOrder].pAnimation->GetAnimationProgress();
	if (IS_PRESS(KEY_TYPE::X) && fProgress > 0.75f && iOrder < m_iMaxCount - 1)
	{
		m_eActiveAttackOrder = static_cast<ATTACK_ORDER>(iOrder + 1);
		m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
	}

	if (m_arrAttackInfo[iEnum][iOrder].pAnimation->IsTriggerFrame())
	{
		// 미사일 발사
		CreateBaseProjectileAndAddedToScene();
		m_arrAttackInfo[iEnum][iOrder].pAnimation->CheckToTriggerFrame();
	}
}

void HighWarlockAttack::Enter()
{
	m_pSkul.lock()->PlayAnimation(m_eActiveAttackOrder, false);
}

void HighWarlockAttack::Exit()
{
	m_eActiveAttackOrder = ATTACK_ORDER::ATTACK_A;
}

void HighWarlockAttack::CreateBaseProjectileAndAddedToScene()
{
	shared_ptr<HighWarlockBaseProjectile> pProjectile = GET_SINGLE(ObjectFactory)->CreateObjectHavePhysicalFromPool<HighWarlockBaseProjectile>(L"Forward", false, ACTOR_TYPE::KINEMATIC, GEOMETRY_TYPE::SPHERE, Vec3(20.f, 20.f, 1.f));
	pProjectile->AddComponent(make_shared<Animator>());
	pProjectile->AddComponent(make_shared<Movement>());

	Vec3 vPlayerPos = m_pSkul.lock()->GetTransform()->GetWorldPosition();
	Vec2 vGlobalOffset = m_pSkul.lock()->GetTransform()->GetGlobalOffset();
	int32 iRandomY = RANDOM(-30, 30);
	vPlayerPos.y += iRandomY + vGlobalOffset.y;
	pProjectile->GetTransform()->SetLocalPosition(vPlayerPos);

	uint32 iDirection = static_cast<uint8>(m_pSkul.lock()->GetDirection());
	pProjectile->GetRigidBody()->SetVelocity(Vec3(iDirection ? -m_fBaseProjectileSpeed : m_fBaseProjectileSpeed, 0.f, 0.f));

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"HighWarlock_BaseProjectile", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_projectile.anim");
	pProjectile->GetAnimator()->AddAnimation(L"HighWarlock_BaseProjectile", pAnimation);
	pProjectile->GetAnimator()->Play(L"HighWarlock_BaseProjectile", true);

	shared_ptr<Animation> pDespawnAnimation = GET_SINGLE(Resources)->LoadAnimation(L"HighWarlock_BaseProjectile_Despawn", L"..\\Resources\\Animation\\HighWarlock\\highwarlock_projectile_despawn.anim");
	pProjectile->GetAnimator()->AddAnimation(L"HighWarlock_BaseProjectile_Despawn", pDespawnAnimation);

	pProjectile->SetDirection(m_pSkul.lock()->GetDirection());
	pProjectile->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pProjectile, eSceneType));
}
