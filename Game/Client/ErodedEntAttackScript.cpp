#include "pch.h"
#include "ErodedEntAttackScript.h"
#include "ErodedEnt.h"
#include "Animator.h"
#include "Animation.h"
#include "Transform.h"
#include "Player.h"
#include "Scenes.h"
#include "Scene.h"
#include "Engine.h"
#include "SoundSource.h"
#include "ComponentObject.h"
#include "Resources.h"

ErodedEntAttackScript::ErodedEntAttackScript()
{
}

ErodedEntAttackScript::~ErodedEntAttackScript()
{
}

void ErodedEntAttackScript::LateUpdate()
{
	weak_ptr<ErodedEnt> pErodedEnt = static_pointer_cast<ErodedEnt>(GetGameObject());

	if (MONSTER_STATE::ATTACK == pErodedEnt.lock()->GetMonsterState())
	{
		if (GetAnimator()->GetActiveAnimation()->IsHitFrame())
		{
			shared_ptr<Sound> pSound = GET_SINGLE(Resources)->Load<Sound>(L"Ent_Atk_Ready", L"..\\Resources\\Sound\\Ent_Atk_Ready.wav");
			SCENE_SOUND->SetClip(pSound);
			SCENE_SOUND->Play();

			Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

			Vec3 vVolume = Vec3(300.f, 300.f, 1.f);
			weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();
			Vec3 vPlayerPos = pPlayer.lock()->GetTransform()->GetPhysicalPosition();

			Vec3 vDiff = vPlayerPos - vMyPos;

			Vec3 vLeftTop = Vec3(vMyPos.x - vVolume.x / 2.f, vMyPos.y + vVolume.y / 2.f, 0.f);
			Vec3 vRightBtm = Vec3(vMyPos.x + vVolume.x / 2.f, vMyPos.y - vVolume.y / 2.f, 0.f);

			if (vPlayerPos.x > vLeftTop.x && vPlayerPos.x < vRightBtm.x &&
				vPlayerPos.y > vRightBtm.y && vPlayerPos.y < vLeftTop.y)
			{
				pPlayer.lock()->TakeDamage(4);
				FONT->DrawDamage(DAMAGE_TYPE::FROM_MONSTER, 4.f, vPlayerPos);
			}

			GetAnimator()->GetActiveAnimation()->CheckToHitFrame();
		}
	}
}
