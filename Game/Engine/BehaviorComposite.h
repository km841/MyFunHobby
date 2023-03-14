#pragma once
#include "BehaviorNode.h"

class BehaviorComposite
	: public BehaviorNode
{
public:
	BehaviorComposite() = default;
	virtual ~BehaviorComposite() { }

public:
	void AddChild(shared_ptr<BehaviorNode> pChild);

protected:
	std::vector<shared_ptr<BehaviorNode>> m_vChildren;

};