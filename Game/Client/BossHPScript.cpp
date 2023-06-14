#include "pch.h"
#include "BossHPScript.h"
#include "Monster.h"
#include "MeshRenderer.h"
#include "Material.h"

BossHPScript::BossHPScript(shared_ptr<Monster> pMonster)
	:m_pBoss(pMonster)
{
}

BossHPScript::~BossHPScript()
{
}

void BossHPScript::LateUpdate()
{
	// Monster HP Setting
	float fRatio = m_pBoss.lock()->GetStatus()->GetHPRatio();
	GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
}
