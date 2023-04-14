#include "pch.h"
#include "AI.h"
#include "Selector.h"
#include "Sequence.h"

AI::AI()
	: Component(COMPONENT_TYPE::AI)
{
}

AI::~AI()
{
}

void AI::Update()
{
	if (m_pRoot)
		m_pRoot->Run();
}
