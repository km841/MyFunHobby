#pragma once
#include "BehaviorComposite.h"

// 자식 노드 중 하나가 Success를 반환하면 바로 Success를 반환한다
// OR 게이트와 같은 역할
class Selector
	: public BehaviorComposite
{
public:
	Selector() = default;
	virtual ~Selector() { }

public:
	virtual BEHAVIOR_RESULT Run() override;


private:


};