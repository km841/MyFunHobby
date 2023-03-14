#include "pch.h"
#include "BehaviorComposite.h"

void BehaviorComposite::AddChild(shared_ptr<BehaviorNode> pChild)
{
	m_vChildren.push_back(pChild);
}
