#include "pch.h"
#include "ChimeraFallParticlesScript.h"
#include "Transform.h"
#include "Clock.h"
#include "RigidBody.h"
#include "EventManager.h"
#include "ObjectRemoveToSceneEvent.h"

ChimeraFallParticlesScript::ChimeraFallParticlesScript()
{
}

ChimeraFallParticlesScript::~ChimeraFallParticlesScript()
{
}

void ChimeraFallParticlesScript::LateUpdate()
{
	Vec3 vMyPos = GetTransform()->GetPhysicalPosition();
	if (vMyPos.y < -1000.f)
		GET_SINGLE(EventManager)->AddEvent(make_unique< ObjectRemoveToSceneEvent>(GetGameObject(), SCENE_TYPE::DUNGEON));
}
