#include "pch.h"
#include "BossHPScript.h"
#include "Monster.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "EventManager.h"
#include "ObjectRemoveToSceneEvent.h"

BossHPScript::BossHPScript(shared_ptr<Monster> pMonster)
	:m_pBoss(pMonster)
{
}

BossHPScript::~BossHPScript()
{
}

void BossHPScript::LateUpdate()
{
	if (m_pBoss.lock())
	{
		// Monster HP Setting
		float fRatio = m_pBoss.lock()->GetStatus()->GetHPRatio();
		GetMeshRenderer()->GetMaterial()->SetFloat(0, fRatio);
	}
	else
	{
		GET_SINGLE(EventManager)->AddEvent(make_unique<ObjectRemoveToSceneEvent>(GetGameObject(), SCENE_TYPE::DUNGEON));
	}
}
