#include "pch.h"
#include "IfPlayerPosXExceedsN.h"
#include "Player.h"
#include "Scenes.h"
#include "Transform.h"

IfPlayerPosXExceedsN::IfPlayerPosXExceedsN(float fPlayerX)
	: m_fPlayerX(fPlayerX)
{
}

bool IfPlayerPosXExceedsN::IsTrigger()
{
	weak_ptr<Player> pPlayer = GET_SINGLE(Scenes)->GetActiveScene()->GetPlayer();

	Vec3 vPlayerPos = pPlayer.lock()->GetTransform()->GetPhysicalPosition();

	return vPlayerPos.x > m_fPlayerX;
}
