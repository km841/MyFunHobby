#include "pch.h"
#include "DarkMirrorReflectionScript.h"
#include "Player.h"
#include "Animator.h"
#include "Animation.h"
#include "Texture.h"
#include "Resources.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Skul.h"
#include "Transform.h"

DarkMirrorReflectionScript::DarkMirrorReflectionScript(shared_ptr<Player> pPlayer)
	: m_pPlayer(pPlayer)
{
}

DarkMirrorReflectionScript::~DarkMirrorReflectionScript()
{
}

void DarkMirrorReflectionScript::LateUpdate()
{
	if (!m_pPlayer.lock()->GetActiveSkul()->GetAnimator()->GetActiveAnimation())
		return;

	Vec3 vPlayerPos = m_pPlayer.lock()->GetTransform()->GetPhysicalPosition();
	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();

	//GetTransform()->SetLocalScale(m_pPlayer.lock()->GetActiveSkul()->GetTransform()->GetLocalScale());

	const FrameData& currFrameData = m_pPlayer.lock()->GetActiveSkul()->GetAnimator()->GetActiveAnimation()->GetCurFrameData();
	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(currFrameData.szTexPath, currFrameData.szTexPath);
	assert(pTexture);

	DIRECTION eDirection = m_pPlayer.lock()->GetDirection();

	Vec3 vSpriteSize = pTexture->GetTexSize();
	Vec2 vLTPos = Vec2(currFrameData.vLTPos.x / vSpriteSize.x, currFrameData.vLTPos.y / vSpriteSize.y);
	Vec2 vSize = Vec2(currFrameData.vSize.x / vSpriteSize.x, currFrameData.vSize.y / vSpriteSize.y);
	Vec2 vOffset = Vec2(currFrameData.vOffset.x / vSpriteSize.x, currFrameData.vOffset.y / vSpriteSize.y);
	Vec2 vAtlasSize = Vec2(100.f / vSpriteSize.x, 100.f / vSpriteSize.y);

	GetMeshRenderer()->GetMaterial()->SetInt(0, 1);
	GetMeshRenderer()->GetMaterial()->SetInt(1, static_cast<uint8>(eDirection));
	GetMeshRenderer()->GetMaterial()->SetVec2(0, vLTPos);
	GetMeshRenderer()->GetMaterial()->SetVec2(1, vSize);
	GetMeshRenderer()->GetMaterial()->SetVec2(2, vAtlasSize);
	GetMeshRenderer()->GetMaterial()->SetVec2(3, vOffset);
	GetMeshRenderer()->GetMaterial()->SetTexture(1, pTexture);
}
