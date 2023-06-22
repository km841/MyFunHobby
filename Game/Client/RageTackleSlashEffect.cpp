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
				vImpulse = Vec3(iDirection ? -300.f : 300.f, 100.f, 0.f);
				break;
			case SLASH_KIND::B:
				vImpulse = Vec3(0.f, 100.f, 0.f);
				break;
			case SLASH_KIND::C:
				vImpulse = Vec3(0.f, 100.f, 0.f);
				break;
			case SLASH_KIND::D:
				vImpulse = Vec3(0.f, 100.f, 0.f);
				break;
			case SLASH_KIND::E:
				vImpulse = Vec3(0.f, 100.f, 0.f);
				break;
			}

			MonsterTakeDamageAndImpulse(vObjectPos, vVolume);

			GET_SINGLE(CollisionManager)->SetForceInLayer(LAYER_TYPE::PARTICLE, vObjectPos, vVolume, vImpulse);
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

void RageTackleSlashEffect::MonsterTakeDamageAndImpulse(const Vec3& vPos, const Vec3& vVolume)
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
				vImpulse = Vec3(iDirection ? -1000.f : 300.f, 0.f, 0.f);
				break;
			case SLASH_KIND::E:
				vImpulse = Vec3(iDirection ? -500.f : 500.f, 100.f, 0.f);
				break;
			}

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

				pMonster.lock()->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleAliveCount(30);
				pMonster.lock()->GetParticleGenerator().lock()->GetParticleSystem()->SetParticleDirection(Vec3(static_cast<float>(RANDOM(0, 300)), 1000.f, 0.f));
			}
		}
	}
}
