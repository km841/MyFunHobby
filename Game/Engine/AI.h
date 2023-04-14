#pragma once
#include "Component.h"
class Selector;

class AI :
    public Component
{
public:
	AI();
	virtual ~AI();
	
public:
	virtual void Update();

public:
	weak_ptr<Selector> GetBehaviorRootNode() { return m_pRoot; }
	void			   SetBehaviorRootNode(shared_ptr<Selector> pRoot) { m_pRoot = pRoot; }

private:
	shared_ptr<Selector> m_pRoot;

};

