#include "pch.h"
#include "ObjectFollowScript.h"
#include "Player.h"
#include "Transform.h"

ObjectFollowScript::ObjectFollowScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

ObjectFollowScript::~ObjectFollowScript()
{
}

void ObjectFollowScript::LateUpdate()
{
	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	vPlayerPos.z -= 5.f;
	GetTransform()->SetLocalPosition(vPlayerPos);
}
