#include "pch.h"
#include "MonsterHealthBarShowScript.h"
#include "Engine.h"
#include "MonsterHPHUD.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Monster.h"

MonsterHealthBarShowScript::MonsterHealthBarShowScript(shared_ptr<MonsterHPHUD> pHealthBar)
	: m_pHealthBar(pHealthBar)
{
}

MonsterHealthBarShowScript::~MonsterHealthBarShowScript()
{
}

void MonsterHealthBarShowScript::LateUpdate()
{
	float fRatio = m_pHealthBar.lock()->GetMonster().lock()->GetStatus()->GetHPRatio();

	float fWidth = static_cast<float>(g_pEngine->GetWidth());
	float fHeight = static_cast<float>(g_pEngine->GetHeight());

	const Vec3& vParentPos = GetTransform()->GetParent().lock()->GetLocalPosition();
	const Vec3& vMyPos = vParentPos + GetTransform()->GetLocalPosition();

	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	GetMeshRenderer()->GetMaterial()->SetVec2(0, Vec2(160.f, 3.f));
	GetMeshRenderer()->GetMaterial()->SetVec2(1, Vec2(fWidth / 1.25f, fHeight / 1.25f));
	GetMeshRenderer()->GetMaterial()->SetVec2(2, Vec2(vMyPos.x, vMyPos.y));
}
