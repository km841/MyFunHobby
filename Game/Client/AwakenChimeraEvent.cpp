#include "pch.h"
#include "AwakenChimeraEvent.h"
#include "Chimera.h"
#include "Scenes.h"
#include "Scene.h"
#include "Clock.h"

AwakenChimeraEvent::AwakenChimeraEvent(shared_ptr<ConditionBlock> pConditionBlock, shared_ptr<Chimera> pChimera)
	: DungeonEvent(DUNGEON_EVENT_KIND::AWAKEN_CHIMERA, pConditionBlock)
	, m_pChimera(pChimera)
{
}

AwakenChimeraEvent::~AwakenChimeraEvent()
{
}

void AwakenChimeraEvent::Update()
{
	DungeonEvent::Update();
}

void AwakenChimeraEvent::ExecuteEvent()
{
	// Alchemist Destroy
	GET_SINGLE(Clock)->Play();
	m_pChimera.lock()->Enable();
	m_pChimera.lock()->AddAnimation("Appear", 0.f, false);
	m_pChimera.lock()->AddAnimation("Roar_Start", 0.f, false);
	m_pChimera.lock()->AddAnimation("Roar", 2.f, false);
	m_pChimera.lock()->AddAnimation("Roar_Loop", 0.f);
	m_pChimera.lock()->AddAnimation("Roar_Start", 2.f, false);
	m_pChimera.lock()->AddAnimation("Roar", 2.f, false);
	m_pChimera.lock()->AddAnimation("Roar_Loop", 0.f);
	// Chimera Enable & Play Animation
}
