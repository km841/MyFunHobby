#include "pch.h"
#include "RageTackleSlashEffect.h"
#include "Animator.h"
#include "Animation.h"
#include "Scenes.h"
#include "Scene.h"
#include "EventManager.h"
#include "ObjectReturnToPoolEvent.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "Monster.h"
#include "RigidBody.h"
#include "Engine.h"
#include "ForceOnObjectEvent.h"
#include "GlobalEffect.h"
#include "ParticleSystem.h"
#include "AnimationGlobalEffect.h"
#include "ObjectFactory.h"
#include "Resources.h"
#include "Player.h"
#include "Sound.h"
#include "SoundSource.h"
#include "Resources.h"
#include "ComponentObject.h"

POOL_INIT(RageTackleSlashEffect);
RageTackleSlashEffect::RageTackleSlashEffect()
	: GameObject(LAYER_TYPE::LOCAL_EFFECT)
	, m_eSlashKind(SLASH_KIND::A)
{
}

RageTackleSlashEffect::~RageTackleSlashEffect()
{
}

void RageTackleSlashEffect::Awake()
{
	GameObject::Awake();
}

void RageTackleSlashEffect::Start()
{
	GameObject::Start();
}

void RageTackleSlashEffect::Update()
{
	GameObject::Update();
	if (GetAnimator())
	{
		if (GetAnimator()->GetActiveAnimation()->IsFinished())
		{
			SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectReturnToPoolEvent>(shared_from_this(), eSceneType));
		}

		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			Vec3 vObjectPos = GetTransform()->GetWorldPosition();
			Vec3 vVolume =GetTransform()->GetLocalScale();

			Vec3 vImpulse = {};

			uint8 iDirection = static_cast<uint8>(GetDirection());
			switch (m_eSlashKind)
			{
			case SLASH_KIND::A:
				vImpulse = Vec3(iDirection ? -300.f : 300.f, 300.f, 0.f);
				break;
			case SLASH_KIND::B:
				vImpulse = Vec3(iDirection ? -300.f : 300.f, -300.f, 0.f);
				break;
			case SLASH_KIND::C:
				vImpulse = Vec3(iDirection ? -1000.f : 1000.f, 0.f, 0.f);
				break;
			case SLASH_KIND::D:
				vImpulse = Vec3(iDirection ? -1000.f : 1000.f, 0.f, 0.f);
				break;
			case SLASH_KIND::E:
				vImpulse = Vec3(iDirection ? -500.f : 500.f, 100.f, 0.f);
				break;
			}

			MonsterTakeDamageAndImpulse(vObjectPos, vVolume, vImpulse);

			

			vImpulse.y += 500.f;
			vImpulse.x += 500.f;
			GET_SINGLE(CollisionManager)->SetForceInLayer(LAYER_TYPE::PARTICLE, vObjectPos, vVolume, vImpulse * 2.f);
			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}
	}

}

void RageTackleSlashEffect::LateUpdate()
{
	GameObject::LateUpdate();
}

void RageTackleSlashEffect::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void RageTackleSlashEffect::MonsterTakeDamageAndImpulse(const Vec3& vPos, const Vec3& vVolume, const Vec3& vImpulse)
{
	auto& vGameObjects = GET_SINGLE(Scenes)->GetActiveScene()->GetGameObjects(LAYER_TYPE::MONSTER);
	Vec3 vLeftTop = Vec3(vPos.x - vVolume.x / 2.f, vPos.y + vVolume.y / 2.f, 0.f);
	Vec3 vRightBtm = Vec3(vPos.x + vVolume.x / 2.f, vPos.y - vVolume.y / 2.f, 0.f);

	for (auto& pGameObject : vGameObjects)
	{
		weak_ptr<Monster> pMonster = static_pointer_cast<Monster>(pGameObject);

		if (MONSTER_STATE::DEAD == pMonster.lock()->GetMonsterState())
			continue;

		Vec3 vObjectPos = pGameObject->GetTransform()->GetPhysicalPosition();
		Vec3 vDamagePos = vObjectPos;
		if (vPos == vObjectPos)
			continue;

		if (vObjectPos.x > vLeftTop.x && vObjectPos.x < vRightBtm.x &&
			vObjectPos.y > vRightBtm.y && vObjectPos.y < vLeftTop.y)
		{
			float fRandomAngular = static_cast<float>(RANDOM(-10, 10));
			pGameObject->GetRigidBody()->SetAngularVelocityForDynamic(PxVec3(0.f, 0.f, fRandomAngular));
			float fDamage = static_cast<float>(RANDOM(10, 15));

			pGameObject->GetStatus()->TakeDamage(static_cast<uint32>(fDamage));
			if (!pGameObject->GetStatus()->IsAlive())
			{
				pMonster.lock()->SetMonsterState(MONSTER_STATE::DEAD);
				//pMonster.lock()->SetParticleDir(Vec3(0.f, 400.f, 0.f));
				vDamagePos.y += vImpulse.y / 6.f;
				FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vDamagePos);
				continue;
			}
			else
			{
				if (MONSTER_TYPE::NORMAL == pMonster.lock()->GetMonsterType())
				{
					vDamagePos.y += vImpulse.y / 6.f;
					FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vDamagePos);

					pMonster.lock()->SetMonsterState(MONSTER_STATE::WEAK_HIT);

					if (vImpulse != Vec3::Zero)
						GET_SINGLE(EventManager)->AddEvent(make_unique<ForceOnObjectEvent>(pGameObject, Conv::Vec3ToPxVec3(vImpulse)));
				}

				else
				{
					FONT->DrawDamage(DAMAGE_TYPE::FROM_PLAYER_MELEE, fDamage, vObjectPos);
				}

				CreateHitEffectAndAddedScene(vObjectPos);

				pMonster.lock()->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleAliveCount(30);
				pMonster.lock()->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleDirection(Vec3(static_cast<float>(RANDOM(0, 300)), 500.f, 0.f));
			}

			// Sound
			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Berserker_Slash_Hit", L"..\\Resources\\Sound\\Hit_Sword_Large.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();
			//Berserker_Slash_Hit
		}
	}
}

void RageTackleSlashEffect::CreateHitEffectAndAddedScene(Vec3 vMonsterPos)
{
	shared_ptr<AnimationGlobalEffect> pHitEffect = GET_SINGLE(ObjectFactory)->CreateObjectHasNotPhysicalFromPool<AnimationGlobalEffect>(L"Forward");
	vMonsterPos.z -= 5.f;
	int32 iRandomX = RANDOM(20, 50);
	int32 iRandomY = RANDOM(0, 30);

	int32 iRandomDegree = RANDOM(-30, 30);
	float fRandomRadian = (iRandomDegree * XM_PI) / 180.f;

	DIRECTION eDirection =GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer()->GetDirection();
	switch (eDirection)
	{
	case DIRECTION::RIGHT:
		vMonsterPos.x += iRandomX;
		vMonsterPos.y -= iRandomY;
		break;
	case DIRECTION::LEFT:
		vMonsterPos.x -= iRandomX;
		vMonsterPos.y -= iRandomY;
		break;
	}

	vMonsterPos.z -= 1.0f;

	pHitEffect->GetTransform()->SetLocalRotation(Vec3(0.f, 0.f, fRandomRadian));
	pHitEffect->GetTransform()->SetLocalPosition(vMonsterPos);
	pHitEffect->AddComponent(make_shared<Animator>());

	shared_ptr<Animation> pAnimation = GET_SINGLE(Resources)->LoadAnimation(L"Berserker_Hit", L"..\\Resources\\Animation\\DevilBerserker\\berserker_hit.anim");
	pHitEffect->GetAnimator()->AddAnimation(L"Berserker_Hit", pAnimation);
	pHitEffect->GetAnimator()->Play(L"Berserker_Hit", false);

	pHitEffect->Awake();
	SCENE_TYPE eSceneType = GET_SINGLE(Scenes)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectAddedToSceneEvent>(pHitEffect, eSceneType));
}
