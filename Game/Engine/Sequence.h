#pragma once
#include "BehaviorComposite.h"

// 자식 노드 중 하나가 Failure를 반환하면 바로 Failure를 반환한다
// AND 게이트와 같은 역할
class Sequence
	: public BehaviorComposite
{
public:
	Sequence() = default;
	virtual ~Sequence() { }

public:
	virtual BEHAVIOR_RESULT Run() override;
};

