#pragma once
#include "Component.h"
class BehaviorNode;

class AI :
    public Component
{
public:
	AI();
	virtual ~AI();
	
public:
	virtual void Update();

public:
	weak_ptr<BehaviorNode> GetBehaviorRootNode() { return m_pRoot; }
	void				   SetBehaviorRootNode(shared_ptr<BehaviorNode> pRoot) { m_pRoot = pRoot; }

private:
	shared_ptr<BehaviorNode> m_pRoot;

};

