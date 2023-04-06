#include "pch.h"
#include "GlobalEffectSettingScript.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "GameObject.h"

GlobalEffectSettingScript::GlobalEffectSettingScript()
{
}

GlobalEffectSettingScript::~GlobalEffectSettingScript()
{
}

void GlobalEffectSettingScript::LateUpdate()
{
	GetGameObject()->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);
}
