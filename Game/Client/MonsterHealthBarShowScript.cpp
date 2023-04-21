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
}
